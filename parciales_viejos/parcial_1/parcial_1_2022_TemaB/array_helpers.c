/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"

/**
* @brief returns true when reach last entry in flight table
* @return True when is the last entre of the flight table, False otherwise
*/
static bool is_last_line(unsigned int hour, unsigned int type) {
  return  hour == HOURS - 1u && type == TYPE - 1u;
}

void array_dump(DeliveryTable a) {
  for (unsigned int type = 0u; type < TYPE; ++type) {
    for (unsigned int hour = 0u; hour < HOURS; ++hour) {
      Flight f = a[type][hour];
      fprintf(stdout, "%c: flight with %u %s arrived at %u:00", f.code, f.items_amount, f.type == 0 ? "boxes" : "letters", f.hour - 1);
      if (!is_last_line(hour, type)) {
        fprintf(stdout, "\n");
      }
    }
  }
}

unsigned int extra_space_fee_cost (DeliveryTable a) {
  unsigned int extra = 0u;
  unsigned int boxes = 0u;
  unsigned int letters = 0u;

  for (unsigned int c = 0u; c <= FEE_CLOSE_HOUR; c++) {
    boxes = boxes + a[0][c].items_amount;
    letters = letters + a[1][c].items_amount;
  }

  if (boxes > MAX_ALLOWED_BOXES) {
    extra = extra + (boxes - MAX_ALLOWED_BOXES) * BOX_PENALTY;
  }

  if (letters > MAX_ALLOWED_LETTERS) {
    extra = extra + (letters - MAX_ALLOWED_LETTERS) * LETTER_PENALTY;
  }

  return extra;
}


void array_from_file(DeliveryTable array, const char *filepath) {
  FILE *file = NULL;

  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  char code;
  while (!feof(file)) {
    int res = fscanf(file, "_%c_", &code);
    if (res != 1) {
      fprintf(stderr, "Invalid file.\n");
      exit(EXIT_FAILURE);
    }

    /* COMPLETAR: Generar y guardar ambos Flight en el array multidimensional */
    Flight flight_boxes = flight_from_file(file, code, boxes);
    Flight flight_letters = flight_from_file(file, code, letters);

    array[boxes][flight_boxes.hour - 1] = flight_boxes;
    array[letters][flight_letters.hour - 1] = flight_letters;
  }
}
