# Playlist

Et simpelt playlist-håndteringssystem implementeret i C ved hjælp af en singly linked list. Programmet kan indlæse, modificere og gemme playlists med tusindvis af tracks.

## Beskrivelse

Dette program demonstrerer brugen af en singly linked list til at håndtere en musikplaylist. Linked lists er mere effektive end arrays til dynamiske operationer som indsættelse og sletning, især når man arbejder med store datasæt.

## Funktionalitet

- Indlæs tracks fra en tekstfil (`playlist.txt`)
- Vis alle tracks med nummerering
- Slet track på en specifik position
- Indsæt ny track på en specifik position
- Gem modificeret playlist til fil (`playlist-out.txt`)
- Automatisk hukommelseshåndtering (allokering og frigivelse)

## Fordele ved Linked List over Array

| Feature | Array | Linked List |
|---------|-------|-------------|
| Indsættelse midt i listen | O(n) - skal flytte elementer | O(1) - kun opdater pointere |
| Sletning midt i listen | O(n) - skal flytte elementer | O(1) - kun opdater pointere |
| Dynamisk størrelse | Svær - kræver reallokering | Let - allokér når nødvendigt |
| Hukommelsesforbrug | Kontinuerlig blok | Spredt med overhead for pointere |
| Tilfældig adgang | O(1) - direkte indeksering | O(n) - skal traverse listen |

## Fil struktur

```
main.c                  - Hovedprogram med playlist-operationer
singly_linked_list.h    - Header fil med linked list interface
singly_linked_list.c    - Implementation af linked list funktioner
playlist.txt            - Input fil med tracks
playlist-out.txt        - Output fil (genereres af programmet)
```

## Kompilering

```powershell
clang main.c singly_linked_list.c -o playlist.exe
```

Alternative compilere:
```powershell
gcc main.c singly_linked_list.c -o playlist.exe
cl main.c singly_linked_list.c
```

## Brug

```powershell
./playlist.exe
```

Programmet vil:
1. Indlæse `playlist.txt`
2. Vise alle indlæste tracks
3. Slette track på index 4 (Smells Like Teen Spirit – Nirvana 🤘)
4. Indsætte ny track på index 3 (Tarkan – Şımarık 💋)
5. Vise modificeret playlist
6. Gemme resultatet til `playlist-out.txt`

## Input format (`playlist.txt`)

```
Bad Guy – Billie Eilish 👽
Bohemian Rhapsody - Queen 🎤
Billie Jean – Michael Jackson 🕺
Rolling in the Deep – Adele 🌊
Smells Like Teen Spirit – Nirvana 🤘
```

## Output format (`playlist-out.txt`)

```
Bad Guy – Billie Eilish 👽
Bohemian Rhapsody - Queen 🎤
Billie Jean – Michael Jackson 🕺
Tarkan – Şımarık 💋
Rolling in the Deep – Adele 🌊
```

## Eksempel på kørsel

```
Loaded tracks:
 1: Bad Guy – Billie Eilish 👽
 2: Bohemian Rhapsody - Queen 🎤
 3: Billie Jean – Michael Jackson 🕺
 4: Rolling in the Deep – Adele 🌊
 5: Smells Like Teen Spirit – Nirvana 🤘

Deleted track at index 4: Rolling in the Deep – Adele 🌊

Modified playlist:
 1: Bad Guy – Billie Eilish 👽
 2: Bohemian Rhapsody - Queen 🎤
 3: Billie Jean – Michael Jackson 🕺
 4: Tarkan – Şımarık 💋
 5: Smells Like Teen Spirit – Nirvana 🤘

Playlist saved to playlist-out.txt
```

## Datastruktur

### Node struktur
```c
typedef struct Node {
    void *data;           // Pointer til track data
    struct Node *next;    // Pointer til næste node
} Node;
```

### Track data
```c
typedef char Data[TRACK_TITLE_SIZE];  // 60 tegn per track
```

## Nøglefunktioner

### `singly_linked_list.c`

- **`insert_at(Node **list, size_t index, Node *new_node)`**
  - Indsætter en ny node på en specifik position
  - Håndterer indsættelse ved start, midten og slutningen

- **`delete_at(Node **list, size_t index)`**
  - Sletter node på en specifik position
  - Returnerer data-pointeren (skal frigives af caller)

- **`append(Node **list, Node *new_node)`**
  - Tilføjer node til slutningen af listen
  - O(n) kompleksitet pga. traversering

- **`free_list(Node **list)`**
  - Frigiver al hukommelse brugt af listen
  - Itererer gennem alle nodes og frigør både data og node

### `main.c`

- **`remove_newline_if_exists(char *line)`**
  - Fjerner trailing newline fra indlæste linjer

- **`load_file(const char *filename, Node **list)`**
  - Læser tracks fra fil linje for linje
  - Opretter nodes og tilføjer dem til listen

- **`save_file(const char *filename, Node *list)`**
  - Skriver alle tracks fra listen til fil

- **`print_tracks(const Node *playlist)`**
  - Udskriver alle tracks med nummerering

## Tekniske detaljer

- **Dynamisk hukommelse**: Bruger `malloc()` til at allokere nodes og track data
- **Void pointere**: `data` er `void*` for generisk brug (kan holde hvilken som helst datatype)
- **Type casting**: Data castes til `(char *)` når den udskrives
- **Newline håndtering**: Fjerner `\n` fra `fgets()` output
- **Fejlhåndtering**: Tjekker om filer kan åbnes, afslutter med fejl hvis ikke
- **Hukommelsesrensning**: `free_list()` frigiver al allokeret hukommelse

## Begrænsninger

- Maksimal track-længde: 60 tegn (defineret i `TRACK_TITLE_SIZE`)
- Filnavne er hardcoded (`playlist.txt` og `playlist-out.txt`)
- Ingen GUI - kun kommandolinje
- Indeksering starter ved 0 (men vises fra 1 til brugeren)

## Mulige udvidelser

### Grundlæggende
- Tilføj kommandolinje-argumenter for filnavne
- Interaktiv menu til brugerinput
- Søgefunktion efter track-navn eller kunstner
- Sortering af playlist (alfabetisk, efter kunstner, etc.)

### Avanceret
- Doubly linked list for bedre navigation (forud og tilbage)
- Hash table for O(1) track lookup
- Persistent storage med database (SQLite)
- Network streaming integration
- GUI med raylib eller GTK

### Interaktivt CLI eksempel
```
Playlist Menu:
1. List all tracks
2. Add track
3. Remove track
4. Save playlist
5. Exit
Enter choice:
```

## Activity 61 svar: Array vs Linked List

**Array implementation:**
- **Add track**: `O(1)` ved slutningen hvis plads, ellers `O(n)` for reallokering
- **Remove track**: `O(n)` - skal flytte alle efterfølgende elementer
- **List tracks**: `O(n)` - simpel iteration

**Ulemper ved arrays:**
- Fast størrelse eller dyr reallokering
- Ineffektiv indsættelse/sletning midt i
- Spild af hukommelse ved over-allokering

**Linked list fordele:**
- Nem dynamisk størrelse
- Effektiv indsættelse/sletning (`O(1)` hvis man har pointeren)
- Ingen hukommelsesspild ved over-allokering

**Linked list ulemper:**
- Ingen tilfældig adgang - skal traverse
- Ekstra hukommelse til pointere
- Dårligere cache-lokalitet

## License

Til uddannelsesformål.
