/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"
#include "character.h"

void array_dump(CharacterList array) {
  for (alignment_t alignment=good; alignment<CHARACTER_ALIGNMENTS; ++alignment) {
    for (charttype_t charttype=physical; charttype < CHARACTER_TYPES; ++charttype) {
      Character character = array[charttype][alignment];

      char *str_alignment = (character.alignment == good) ? "Good" : "Evil";
      char *str_alive = (character.alive) ? "Yes" : "Nope";

      fprintf(stdout,
              "Character '%s': Life=%u/100, Strength=%u/10, Agility=%u/10, "
              "alignment='%s', Alive='%s'\n",
              NAMES[character.name], character.life, character.strength,
              character.agility, str_alignment, str_alive);
    }
  }
}

float array_alive_mean_life(CharacterList array) {
  float s_vidas = 0;    
  int characters = 0;
  for (unsigned int i = 0u; i < CHARACTER_TYPES; i++) {
    for (unsigned int j = 0u; j < CHARACTER_ALIGNMENTS; j++) {
      if (array[i][j].alive) {
        s_vidas = s_vidas + array[i][j].life;
        characters++;
      }
    }
  }

  s_vidas = s_vidas / characters;
  
  return s_vidas;
}

unsigned int array_from_file(CharacterList array, const char *filepath) {
  FILE *file = NULL;

  // check if file exists
  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  // read the file
  unsigned int readed = 0;
  while (!feof(file)) {
    charttype_t charttype;
    alignment_t alignment;

    char s_charttype, s_alignment;
    int res=fscanf(file, "[%c %c] " , &s_charttype, &s_alignment);
    if (res != 2) {
        fprintf(stderr, "Error reading type and alignment.\n");
        exit(EXIT_FAILURE);
    }
    /* convertir la letra de `s_charttype` en un valor `charttype_t` y asignarlo
     * a la variable  `charttype`:
     *
     * 'a' --> agile
     * 'p' --> physical
     * 't' --> tank
     * 'm' --> magic
     *
     */

    if (s_charttype == 'a') {
      charttype = agile;
    } else if (s_charttype == 'p') {
      charttype = physical;
    } else if (s_charttype == 't') {
      charttype = tank;
    } else if (s_charttype == 'm') {
      charttype = magic;
    } else {
      fprintf(stderr, "Invalid Character Type.\n");
      exit(EXIT_FAILURE);
    }
    
    /* convertir la letra de `s_alignment` en un valor `aligment_t` y asignarlo
     * a la variable  `alignment`:
     *
     * 'g' --> good
     * 'e' --> evil
     *
     */

    if (s_alignment == 'g') {
      alignment = good;
    } else if (s_alignment == 'e') {
      alignment = evil;
    } else {
      fprintf(stderr, "Invalid Character Alignment.\n");
      exit(EXIT_FAILURE);
    }
    
    // Reads the name and obtains an name_t value
    name_t name = read_character_name(file);

    Character character = character_from_file_line(file, name, alignment);

    array[charttype][alignment] = character;

    ++readed;
  }

  if (readed != 8) {
    fprintf(stderr, "Invalid Number of Records.\n");
    exit(EXIT_FAILURE);
  }
  
  // close the file
  fclose(file);

  return readed;
}
