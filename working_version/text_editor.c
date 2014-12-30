/* Accesses display.c */
/* Is accessed by input.c and interface.c */
#include "input.h"

void free_text_nodes(TextNode* head);
TextNode* make_cell(int width, int height, Coordinates curr, Interface* interface, TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS], TextNode* current);
void make_first_cell(Coordinates curr, Interface* interface, TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS], TextNode* current);
void make_middle_cells(Coordinates curr, Interface* interface, TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS], TextNode* current);
void make_last_cell(Coordinates curr, Interface* interface, TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS], TextNode* current);
void update_text_node(TextNode* current, Interface* interface);
int character_provided(TextNode* cell, char* character);

void set_node_attributes(Interface* interface, int row, int column, TextNode* new_node);
void set_node_text(Interface* interface, char* text, TextNode* new_node);

void write_text_to_cell(Interface* interface, FILE* file_name, int row, int column);

void handle_enter_shuffling(Coordinates active, Interface* interface);
void enter_shuffle(Coordinates active, Interface* interface, char copy[interface->editor_columns][3], char nxt[interface->editor_columns][3]);

int rest_of_row_empty(Coordinates active, Interface* interface);
int entire_row_empty(int row, Interface* interface);

void store_row_backup(Coordinates active, Interface* interface, char backup[interface->editor_columns][3]);
void shift_cells_back_one(Coordinates active,  Interface* interface, char backup[interface->editor_columns][3]);

TextNode* load_text_into_cell(char c, int* row, int* column, Interface* interface, TextNode* current);
void concatenate_to_previous_text(Coordinates active, Coordinates cell, Interface* interface, char copy[interface->editor_columns][3]);
void shift_rows_back_one(Coordinates active, Interface* interface);

void text_after_active_column(Coordinates active, Coordinates cell, Interface* interface, char copy[interface->editor_columns][3]);
void backwrite_start_column(Coordinates active, Coordinates cell, Interface* interface, char copy[interface->editor_columns][3]);
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||//
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||//
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||//

                     /* Text Editor Data Structure */

/* Makes a cell for every grid position (grid size based on window width/height) */
void make_text_editor(int width, int height, Interface* interface) {
   TextNode* current = NULL;
   Coordinates curr;
   for (int row = 0; row < height; row++) {
      for (int column = 0; column < width; column++) {   
         curr.row = row;
         curr.column = column;  
         current = make_cell(width, height, curr, interface, interface->text_editor, current);
      }
   }
}

//creates text cells based on where the current grid position
TextNode* make_cell(int width, int height, Coordinates curr, Interface* interface, 
                    TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS], TextNode* current) {
   if (first_cell(curr)) {
      make_first_cell(curr, interface, text_editor, current);
   }
   else if (!last_cell(curr, *interface)) {
      make_middle_cells(curr, interface, text_editor, current);
   }
   else {
      make_last_cell(curr, interface, text_editor, current);
   }

   return &text_editor[curr.row][curr.column];
}

void make_first_cell(Coordinates curr, Interface* interface, 
                     TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS], TextNode* current) {
   text_editor[curr.row][curr.column] = *allocate_text_node(EMPTY_CELL, NULL, 
                                        interface, curr.row, curr.column);
   text_editor[curr.row][curr.column].next = &interface->text_editor[0][curr.column+1];  
   set_active_text_cell(curr.row, curr.column, interface);
}

void make_middle_cells(Coordinates curr, Interface* interface, 
                       TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS], TextNode* current) {
   text_editor[curr.row][curr.column] = *allocate_text_node(EMPTY_CELL, current, 
                                        interface, curr.row, curr.column);

   //if the text cell is in the final column, its next link is the first cell 
   //of the next row
   if (end_column(curr, *interface)) {
      text_editor[curr.row][curr.column].next = &interface->text_editor[curr.row+1][0];  
   }
   //otherwise, the next link is the next cell in the row
   else {
      text_editor[curr.row][curr.column].next = &interface->text_editor[curr.row][curr.column + 1];
   }
}

void make_last_cell(Coordinates curr, Interface* interface, 
                    TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS], TextNode* current) {
   text_editor[curr.row][curr.column] = *allocate_text_node(EMPTY_CELL, current, 
                                      interface, curr.row, curr.column);
   text_editor[curr.row][curr.column].next = NULL;
}

//updates the text editor based on user input
void update_text_editor(int width, int height, Interface* interface) {
   TextNode* current = &interface->text_editor[0][0];

   while (current != NULL) {
      update_text_node(current, interface);
      current = current->next;
   }

   make_rect(&interface->window, &interface->text_cursor, 
            interface->text_editor_panel.rect.x + 
            (interface->active_txt.column * (FONT_SIZE- 6)),
            interface->text_editor_panel.rect.y + 
            (interface->active_txt.row * (FONT_SIZE + 9.1)),
            3, (FONT_SIZE + 4), 240, 240, 240);
}

TextNode* allocate_text_node(char* text, TextNode* previous_node, 
                             Interface* interface, int row, int column) {
   TextNode* new_node = (TextNode *)malloc(sizeof(TextNode));
   if (new_node == NULL) {
      printf("Cannot Allocate Node\n");
      exit(2);
   }
   new_node->previous = previous_node;
   set_node_attributes(interface, row, column, new_node);
   set_node_text(interface, text, new_node);


   return new_node;
}

void set_node_attributes(Interface* interface, int row, int column, TextNode* new_node) {
   int box_w = (FONT_SIZE- 6);
   int box_h =  (FONT_SIZE + 9);
   int x = (interface->text_editor_panel.rect.x + (column * box_w));
   int y = (interface->text_editor_panel.rect.y + (row * box_h));

   new_node->text_cell.row = row;
   new_node->text_cell.column = column;
   new_node->location.row = y;
   new_node->location.column = x;
   new_node->w = box_w;
   new_node->h = box_h;

   make_rect(&interface->window, &interface->text_editor[row][column].box, x, y, 
            box_w, box_h, 43, 43, 39);
}

void set_node_text(Interface* interface, char* text, TextNode* new_node) {
   strcpy(new_node->character, text);
   /* if there's no character to render, skip make_text */
   if (character_provided(new_node, text)) {
      make_text(&interface->window, &interface->text_editor[new_node->text_cell.row][new_node->text_cell.column].box.rect, 
               240, 240, 240, interface->font, new_node->character);
   }
}

void update_text_node(TextNode* current, Interface* interface) {
   make_rect(&interface->window, &current->box, current->location.column, 
            current->location.row, current->w, current->h, 43, 43, 39);
   /* if there's no character to render, skip make_text */
   if (strcmp(current->character, EMPTY_CELL) != 0) {
      make_text(&interface->window, &current->box.rect, 240, 240, 240, 
               interface->font, current->character);
   }
}

int character_provided(TextNode* cell, char* character) {
   if (strcmp(cell->character, EMPTY_CELL) != 0) {
      return 1;
   }
   return 0;
}

void set_active_text_cell(int row, int column, Interface* interface) {
    interface->active_txt.row = row;
    interface->active_txt.column = column;
}
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||//
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||//
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||//

                      /* Text File Handling */


FILE* open_file(char *file_name) {
    FILE *input_file = fopen(file_name, "r");
    if (input_file == NULL) {
        printf("File does not exist.\n");
        make_file(file_name);
    }
    return input_file;
} 

FILE* make_file(char *file_name) {
    FILE* new_file = fopen(file_name, "w");
    if (new_file != NULL) {
        printf("New file created!\n");
    }  
    else {
        printf("Error: unable to create file!");
        exit(1);
    }
    return new_file;
}

void write_text_to_file(Interface* interface, char* file_name) {
   FILE* user_code = fopen("user_code.artc", "w");
   for (int row = 0; row < interface->editor_rows; row++) {
      for (int column = 0; column < interface->editor_columns; column++) {
         write_text_to_cell(interface, user_code, row, column); 
      }
      fputs("\n", user_code);
   }
   fclose(user_code);
}

void write_text_to_cell(Interface* interface, FILE* file_name, int row, int column) {
   if (strcmp(interface->text_editor[row][column].character, EMPTY_CELL) != 0) {
      fputs(interface->text_editor[row][column].character, file_name);
   }
}

void load_text_into_text_editor(char* file_name, Interface* interface) {
    FILE* challenge = fopen(file_name, "r");
    int row = 0;
    int column = 0;
    char c;
    TextNode* current = &interface->text_editor[row][column];
    
    while ((c = fgetc(challenge)) != EOF) {
      current = load_text_into_cell(c, &row, &column, interface, current);
    }
}

TextNode* load_text_into_cell(char c, int* row, int* column, Interface* interface, TextNode* current) {
   if (c == '\n') {
      *column = 0;
      return &interface->text_editor[++(*row)][(*column)];
   }          
   else {
      strcpy(current->character, &c);
      return current->next; 
   } 
}
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||//
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||//
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||//

                          /* Text Manipulation */

///////////////////////////////////////////////////////////////////////////////
                        /* Carriage Return (Enter) */
///////////////////////////////////////////////////////////////////////////////
void enter_shuffle(Coordinates active, Interface* interface, char copy[interface->editor_columns][3], char move[interface->editor_columns][3]) {
   Coordinates cell;
   cell.column = active.column;
   /* Active row move */
   
   /* hold the row to be moved */
   for (int column = 0; column < interface->editor_columns; column++) {
      strcpy(move[column], interface->text_editor[active.row][cell.column++].character);
   }
  
   /* hold a backup of the next row */
   for (int column = 0; column < interface->editor_columns; column++) {
      strcpy(copy[column], interface->text_editor[active.row + 1][column].character);
   }

   /* copy the move row into the next row */
   for (int column = 0; column < interface->editor_columns; column++) {
         strcpy(interface->text_editor[active.row + 1][column].character, move[column]);
   }

   /* empty the cells that have been moved */
   for (int column = active.column; column < interface->editor_columns; column++) {
      strcpy(interface->text_editor[active.row][column].character, EMPTY_CELL);
   }
   
   /* rest of the rows */
   for (int row = active.row + 1; row < interface->editor_rows; row++) {
      cell.column = active.column;
      /* hold the row to be moved */
      for (int column = 0; column < interface->editor_columns; column++) {
         strcpy(move[column], copy[column]);
      }
      // save a backup of the next row 
      for (int column = 0; column < interface->editor_columns; column++) {
         strcpy(copy[column], interface->text_editor[row + 1][column].character);
      }
      // copy the previous row into the next row
      for (int column = 0; column < interface->editor_columns; column++) {
         strcpy(interface->text_editor[row + 1][column].character, move[column]);
      }
   }
}

void handle_enter_shuffling(Coordinates active, Interface* interface) {
   char copy[interface->editor_columns][3];
   char move[interface->editor_columns][3];
   enter_shuffle(active, interface, copy, move);
}

///////////////////////////////////////////////////////////////////////////////
                                 /* Backspace */
///////////////////////////////////////////////////////////////////////////////


void handle_backwriting(Coordinates active, Interface* interface) {
  Coordinates cell;
  cell.column = active.column;
  cell.row = active.row;

  char copy[interface->editor_columns][3];
    
  /* check whether the cells in the row after the active column contain anything */
  if (!rest_of_row_empty(active, interface)) {;
      text_after_active_column(active, cell, interface, copy);
  }

  /* if the rest of the row is empty */
  else {
    if (entire_row_empty(active.row, interface)) {
      if (entire_row_empty(active.row - 1, interface)) {
        cell.row = cell.row - 1;
        cell.column = 0;
      }
      else {
        find_previous_active_node(&cell, interface);
      }
          //the lines beneath are alsso shifted up one row.
        for (int row = active.row; row < interface->editor_rows; row++) {
          for (int column = 0; column < interface->editor_columns; column++) {
            if (row != 25) {
             strcpy(interface->text_editor[row][column].character, interface->text_editor[row + 1][column].character);
            }
            else {
              strcpy(interface->text_editor[row][column].character, EMPTY_CELL);
            }
          }
        }
      SDL_SetTextInputRect(&interface->text_editor[cell.row][cell.column].box.rect);
      set_active_text_cell(cell.row, cell.column, interface); 
    }
  }
}

void text_after_active_column(Coordinates active, Coordinates cell, Interface* interface, char copy[interface->editor_columns][3]) {
    store_row_backup(active, interface, copy);
    //if the row is not being shifted on to the previous line
    if (!start_column(active)) {
      shift_cells_back_one(active, interface, copy);
    }
    else { 
      backwrite_start_column(active, cell, interface, copy);
    }
}

void backwrite_start_column(Coordinates active, Coordinates cell, Interface* interface, char copy[interface->editor_columns][3]) {
    /* need to check if row above is empty here too! */
   if (entire_row_empty(active.row - 1, interface)) {
     cell.row = cell.row - 1;
     cell.column = 0;
   }
   else {
       //everything on the active row is shifted up and after the previous active cell
      find_previous_active_node(&cell, interface);
   }
   concatenate_to_previous_text(active, cell, interface, copy);
   //the lines beneath are also shifted up one row.
   shift_rows_back_one(active, interface);
   SDL_SetTextInputRect(&interface->text_editor[cell.row][cell.column].box.rect);
   set_active_text_cell(cell.row, cell.column, interface); 
}

void store_row_backup(Coordinates active, Interface* interface, char backup[interface->editor_columns][3]) {
  for (int column = 0; column < interface->editor_columns; column++) {
    strcpy(backup[column], interface->text_editor[active.row][column].character);
  }
}

void shift_cells_back_one(Coordinates active, Interface* interface, char backup[interface->editor_columns][3]) {
   for (int column = active.column; column < interface->editor_columns; column++) {
      strcpy(interface->text_editor[active.row][column - 1].character, backup[column]);
   }  
}

void concatenate_to_previous_text(Coordinates active, Coordinates cell, Interface* interface, char copy[interface->editor_columns][3]) {
   for (int column = active.column; column < interface->editor_columns; column++) {
      strcpy(interface->text_editor[cell.row][cell.column++].character, copy[column]);
   }  
}

void shift_rows_back_one(Coordinates active, Interface* interface) {
   for (int row = active.row; row < interface->editor_rows; row++) {
      for (int column = 0; column < interface->editor_columns; column++) {
         strcpy(interface->text_editor[row][column].character, interface->text_editor[row + 1][column].character);
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
                                 /* Tab */
///////////////////////////////////////////////////////////////////////////////

void indent(Coordinates active, Interface* interface, int direction) {
   Coordinates cell;
   cell.column = active.column;
   char copy[interface->editor_columns][3];
   int tab = 0;
   //if indent
   if (direction == 1) {
      tab = 3;
   }
   //other unindent
   else {
      tab = -3;
   }

   /* save a copy of the row */
   for (int column = active.column; column < interface->editor_columns; column++) {
      strcpy(copy[column], interface->text_editor[active.row][cell.column++].character); 
   }
   cell.column = active.column;
   for (int column = active.column; column < active.column + tab; column++) {
      strcpy(interface->text_editor[active.row][column].character, " ");
   }
   for (int column = active.column+tab; column < interface->editor_columns; column++) {
      strcpy(interface->text_editor[active.row][column].character, copy[column - tab]);  
   }

   //prevents garbage from entering the end of the row
   if (direction != 1) {
      for (int column = interface->editor_columns - 1; column > interface->editor_columns - 4; column --) {
         strcpy(interface->text_editor[active.row][column].character, EMPTY_CELL);
      }
   }

}

///////////////////////////////////////////////////////////////////////////////
                              /* Text Overflow */
///////////////////////////////////////////////////////////////////////////////


void handle_overwriting(Coordinates active, Interface* interface, char* overflow) {
    Coordinates over = active;
    TextNode* current = &interface->text_editor[active.row][active.column];
    char curr[3];
    char nxt[3];

    current = handle_initial_cell(overflow, nxt, curr, current);
  
    shuffle_rest_of_line(active, *interface, current, curr, nxt);

    if (!bottom_row(active, *interface)) {

        if (shuffle_overflow(&over, *interface, nxt)) {

            handle_overwriting(over, interface, nxt);
        }
    }
}

int text_overflow(char* overflow) {
    if (strcmp(overflow, EMPTY_CELL) != 0) {
        return 1;
    }
    return 0;
}


TextNode* handle_initial_cell(char* overflow, char* nxt, char* curr, TextNode* current) {
    //text overflow is where the current text input also affects the next line 
    //this is necessary in our text editor because it has no horizontal scrolling
    //overflow is carried over recursively from the previous instance of the function
    if (text_overflow(overflow)) {
        handle_overflow(nxt, current, overflow, curr);
    }
    else {
        shuffle_active_cell(curr, current, nxt);
    }
    return current->next;
}

//activated if there is a char present in the first column of the next row
//moves the char in column 0 along one cell
void handle_overflow(char* nxt, TextNode* current, char* overflow, char* curr) {
    strcpy(nxt, current->next->character);
    strcpy(current->next->character, overflow);
    strcpy(curr, current->next->character);
}

void shuffle_active_cell(char *curr, TextNode* current, char* nxt) {
    strcpy(curr, current->character);
    strcpy(nxt, current->next->character);
    strcpy(current->next->character, curr);
}

//shuffles all of the cells affected by the inserted character on the row
void shuffle_rest_of_line(Coordinates active, Interface interface, TextNode* current, char* curr, char* nxt) {
    int col = active.column;
    int condition = interface.editor_columns - 1;

    //since the text editor isn't scrolling, the condition for the bottom row simply drops the final column's character
    if (bottom_row(active, interface)) {
        condition -= 1;
    }

    while (col < condition) {
        col++; 
        if (strcmp(nxt, EMPTY_CELL) != 0) {
            current = current->next;
            strcpy(curr, nxt);
            strcpy(nxt, current->character);
            strcpy(current->character, curr);
        }
    }
}

int shuffle_overflow(Coordinates* over, Interface interface, char* nxt) {
    over->row  += 1;
    over->column = 0;
    if (strcmp(interface.text_editor[over->row][0].character, EMPTY_CELL) != 0) {
        if (strcmp(nxt, EMPTY_CELL) != 0) {           
            return 1;
        }
    }
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
                        /* Helper Functions */
///////////////////////////////////////////////////////////////////////////////

int rest_of_row_empty(Coordinates active, Interface* interface) {
  for (int col = active.column; col < interface->editor_columns; col++) {
    if (strcmp(interface->text_editor[active.row][col].character, EMPTY_CELL) != 0) {
      return 0;
    }
  }
  return 1;
}

int entire_row_empty(int row, Interface* interface) {
  for (int col = 0; col < interface->editor_columns; col++) {
    if (strcmp(interface->text_editor[row][col].character, EMPTY_CELL) != 0) {
      return 0;
    }
  }
  return 1;
}

void find_next_active_node(Coordinates* active, Interface* interface) {
   TextNode* current = &interface->text_editor[active->row][active->column];
   while (current->next != NULL && strcmp(current->character, EMPTY_CELL) == 0) {
      current = current->next;
   }
   if (current->next == NULL) {
      active->row = active->row + 1;
      active->column = 0;
   }
   else {
      active->row = current->text_cell.row;
      active->column = current->text_cell.column;
   }
}

void find_previous_active_node(Coordinates* active, Interface* interface) {
   TextNode* current = &interface->text_editor[active->row][active->column];

   while (current->previous != NULL && strcmp(current->previous->character, EMPTY_CELL) == 0) {
      current = current->previous;
   }
     
   if (current->previous == NULL) {
      active->row = active->row - 1;
      active->column = 0;
   }
   else {
      active->row = current->text_cell.row;
      active->column = current->text_cell.column;
   }
}

int final_active_node(Coordinates active, Interface interface) {
   TextNode* current = &interface.text_editor[active.row][active.column];
   if (current->next == NULL) {
      return 1;
   }
   current = current->next;
   while (strcmp(current->character, EMPTY_CELL) == 0 && current->next != NULL) {
      current = current->next;
   }
   if (current->next == NULL) {
      return 1;
   }
   return 0;

}

int top_row(Coordinates active) {
    if (active.row == 0) {
        return 1;
    }
    return 0;
}

int bottom_row(Coordinates active, Interface interface) {
    if (active.row == interface.editor_rows - 1) {
        return 1;
    }
    return 0;
}

int start_column(Coordinates active) {
    if (active.column == 0) {
        return 1;
    }
    return 0;
}

int end_column(Coordinates active, Interface interface) {
    if (active.column == interface.editor_columns - 1) {
        return 1;
    }
    return 0;
}

int first_cell(Coordinates active) {
    if (top_row(active) && start_column(active)) {
        return 1;
    }
    return 0;
}

int last_cell(Coordinates active, Interface interface) {
    if (bottom_row(active, interface) && end_column(active, interface)){
        return 1;
    }
    return 0;
}
