#include "singly_linked_list.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRACK_TITLE_SIZE 60

#define PLAYLIST_IN_PATH "playlist.txt"
#define PLAYLIST_OUT_PATH "playlist-out.txt"
// To avoid unnecessary complexity, we fix the filenames instead of getting them
// through runtime parameters.

typedef char Data[TRACK_TITLE_SIZE];
Node *playlist = NULL;

/// Removes trailing newline from the line, if it exists.
/// Note: Some lines may not have a newline, e.g., last line in a file,
/// therefore we have to check for presence.
char *remove_newline_if_exists(char *line) {
  size_t len = strlen(line);
  if (len > 0 && line[len - 1] == '\n') {
    line[len - 1] = '\0';
  }
  return line;
}

/// Reads lines from at `filename`, creates a node for each line and inserts
/// nodes to `list`.
Node **load_file(const char *filename, Node **list) {
  // Open the file and assign to stream `f`
  FILE *f = fopen(filename, "r");
  if (!f) {
    perror(PLAYLIST_IN_PATH);
    exit(EXIT_FAILURE);
  }
  char line[TRACK_TITLE_SIZE];

  while (
      // Read one line from the stream
      fgets(line, TRACK_TITLE_SIZE, f) != NULL
  ) {
    remove_newline_if_exists(line);

    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->next = NULL;
    Data *data = (Data *)malloc(sizeof(Data));
    new_node->data = data;

    // Copy line to `new_node` and append `new_node` to `list`
    strncpy(*(Data *)new_node->data, line, TRACK_TITLE_SIZE - 1);
    ((char *)new_node->data)[TRACK_TITLE_SIZE - 1] = '\0';
    append(list, new_node);
  }
  fclose(f);
  return list;
}

/// Saves `list` contents to the file at `filename`.
void save_file(const char *filename, Node *list) {
  // Open file
  FILE *f = fopen(filename, "w");
  if (!f) {
    perror(filename);
    exit(EXIT_FAILURE);
  }

  // Move through the list and save the tracks to the file
  // Note: You have to cast the data to print the track to the file as follows:
  // `*(Data *)current->data`, which is the same as `(char *)current->data`.
  // We need this cast, because `data` is a pointer to everything (`void *`).
  Node *current = list;
  while (current != NULL) {
    fprintf(f, "%s\n", (char *)current->data);
    current = current->next;
  }

  fclose(f);
}

void print_tracks(const Node *const playlist) {
  const Node *current = playlist;
  for (size_t i = 1; current; i++, current = current->next)
    printf("%2ld: %s\n", i, (char *)current->data);
}

int main() {
  load_file(PLAYLIST_IN_PATH, &playlist);
  puts("Loaded tracks:");
  print_tracks(playlist);

  // Deletion
  size_t node_index_to_del = 4;
  void *deleted_data = delete_at(&playlist, node_index_to_del);
  if (deleted_data) {
    printf("\nDeleted track at index %zu: %s\n", node_index_to_del, (char *)deleted_data);
    free(deleted_data);
  }

  // Insertion
  Node *new_node = (Node *)malloc(sizeof(Node));
  Data *new_data = (Data *)malloc(sizeof(Data));
  strncpy(*new_data, "Tarkan – Şımarık 💋", TRACK_TITLE_SIZE - 1);
  (*new_data)[TRACK_TITLE_SIZE - 1] = '\0';
  new_node->data = new_data;
  new_node->next = NULL;
  insert_at(&playlist, 3, new_node);
  
  puts("\nModified playlist:");
  print_tracks(playlist);

  save_file(PLAYLIST_OUT_PATH, playlist);
  printf("\nPlaylist saved to %s\n", PLAYLIST_OUT_PATH);
  
  free_list(&playlist);
  return 0;
}
