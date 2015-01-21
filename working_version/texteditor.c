#include "texteditor.h" 

                     /* Text Editor Data Structure */

void initialise_text_editor(Interface* interface, Mode mode, char* file_name) {

    SDL_GetWindowSize(interface->window.win, 
                        &interface->editor_columns, &interface->editor_rows);

    interface->editor_columns /= 27;
    interface->editor_rows /= 27;

    make_text_editor(interface->editor_columns, interface->editor_rows, 
                       interface);
  
    SDL_SetTextInputRect(&interface->text_editor[0][0].box.rect);
    SDL_StartTextInput();

  
    load_text_into_text_editor(interface->default_file, interface);    
}

/* Updates the Text Editor data structure based on user input */
void update_text_editor(int width, int height, Interface* interface) {
    TextNode* current = &interface->text_editor[0][0];
    
    while(current != NULL) {
        update_text_node(current, interface);
        current = current->next;
    }
 
    update_text_cursor(interface);
}

// Makes a cell for every grid position (grid size based on window width/height)
void make_text_editor(int width, int height, Interface* interface) {
    TextNode* current = NULL;
    Coordinates curr;
    for(int row = 0; row < height; row++) {
        for(int column = 0; column < width; column++) {   
            curr.row = row;
            curr.column = column;  
            current = make_cell(width, height, curr, interface, 
                                interface->text_editor, current);
        }
    }
}

void load_text_into_text_editor(char* file_name, Interface* interface) {
    FILE* challenge = fopen(file_name, "r");
    int row = 0;
    int column = 0;
    TextNode* current = &interface->text_editor[row][column];
    char c;
    
    wipe_text_editor(interface);

    while((c = fgetc(challenge)) != EOF) {
      current = load_text_into_cell(c, &row, &column, interface, current);
    }

    SDL_SetTextInputRect(&interface->text_editor[0][0].box.rect);
    set_active_text_cell(0, 0, interface);
    update_text_editor(interface->editor_columns, interface->editor_rows, 
                         interface);
}

TextNode* load_text_into_cell(char c, int* row, int* column, 
                                Interface* interface, TextNode* current) {
  
   if(c == '\n') {
      *column = 0;
      return &interface->text_editor[++(*row)][(*column)];
   }          
   else {
      strcpy(current->character, &c);
      current->character[1] = '\0';
      return current->next; 
   } 
}

/* Creates text cells based on the current grid position */
/* The first cell and last cell have particular requirements */
TextNode* make_cell(int width, int height, Coordinates curr, 
                      Interface* interface, 
                      TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS], 
                      TextNode* current) {

    if(first_cell(curr)) {
        make_first_cell(curr, interface, text_editor, current);
    }
    else if(!last_cell(curr, *interface)) {
        make_middle_cells(curr, interface, text_editor, current);
    }
    else {
        make_last_cell(curr, interface, text_editor, current);   
    }

    return &text_editor[curr.row][curr.column];
}

void make_first_cell(Coordinates curr, Interface* interface, 
                    TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS], 
                    TextNode* current) {

    text_editor[curr.row][curr.column] = *allocate_text_node(EMPTY_CELL, NULL, 
                                              interface, curr.row, curr.column);
    //Set the first cell's only neighbour to be 0, 1.
    text_editor[curr.row][curr.column].next = 
                                      &interface->text_editor[0][curr.column+1];  

    //The first cell is where the cursor starts by default.
    set_active_text_cell(curr.row, curr.column, interface);
}

void make_middle_cells(Coordinates curr, Interface* interface, 
                        TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS], 
                        TextNode* current) {

   text_editor[curr.row][curr.column] = *allocate_text_node(EMPTY_CELL, current, 
                                              interface, curr.row, curr.column);

    /* If the current cell is in the final column of the text editor,
      then its next link will be the cell in the first column of the next row */
    if(end_column(curr, *interface)) {
        text_editor[curr.row][curr.column].next = 
                                         &interface->text_editor[curr.row+1][0];  
    }

    /* Otherwise, the next link is the next cell in the row */
    else {
        text_editor[curr.row][curr.column].next = 
                             &interface->text_editor[curr.row][curr.column + 1];
    }
}

void make_last_cell(Coordinates curr, Interface* interface, 
                      TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS], 
                      TextNode* current) {

    text_editor[curr.row][curr.column] = 
                             *allocate_text_node(EMPTY_CELL, current, interface, 
                                                   curr.row, curr.column);

    /* The last cell has no next link; its only neighbour is in the previous
        column */
    text_editor[curr.row][curr.column].next = NULL;
}

/* Calculate the current position of the text cursor and create it */
void update_text_cursor(Interface* interface) {
    float cursor_x_offset = interface->text_editor_panel.rect.x + 
                            (interface->active_txt.column * CURSOR_X); 
    float cursor_y_offset = interface->text_editor_panel.rect.y + 
                            (interface->active_txt.row * CURSOR_Y);

    make_rect(&interface->window, &interface->text_cursor, 
        cursor_x_offset,
        cursor_y_offset,
        CURSOR_W, CURSOR_H, 220, 220, 220);
}

/* Allocate space for a text node and set its attributes */
TextNode* allocate_text_node(char* text, TextNode* previous_node, 
                             Interface* interface, int row, int column) {

    TextNode* new_node = (TextNode *)malloc(sizeof(TextNode));

    if(new_node == NULL) {
        printf("Cannot Allocate Node\n");
        exit(2);
    }

    new_node->previous = previous_node;
    set_node_attributes(interface, row, column, new_node);
    set_node_text(interface, text, new_node);

    return new_node;
}

void update_text_node(TextNode* current, Interface* interface) {

    make_rect(&interface->window, &current->box, current->location.column, 
            current->location.row, TEXT_CELL_W, TEXT_CELL_H, 43, 43, 39);

    /* if there's no character to render, skip make_text */
    if(!is_empty_cell(current->character)) {
        make_text(&interface->window, &current->box.rect,
                interface->text_ed_font, current->character, 240, 240, 240);
    }
}

void set_node_attributes(Interface* interface, int row, int column, 
                           TextNode* new_node) {

    int x = (interface->text_editor_panel.rect.x  + (column * TEXT_CELL_W));
    int y = (interface->text_editor_panel.rect.y + (row * TEXT_CELL_H));

    new_node->text_cell.row = row;
    new_node->text_cell.column = column;
    new_node->location.row = y;
    new_node->location.column = x;

    make_rect(&interface->window, &interface->text_editor[row][column].box, 
              x, y, TEXT_CELL_W, TEXT_CELL_H, 43, 43, 39);
}

void set_node_text(Interface* interface, char* text, TextNode* new_node) {
    strcpy(new_node->character, text);
    /* if there's no character to render, skip! */
    if(!is_empty_cell(new_node->character)) {
        int row = new_node->text_cell.row;
        int column = new_node->text_cell.column;
        make_text(&interface->window, 
                    &interface->text_editor[row][column].box.rect, 
                    interface->text_ed_font, new_node->character, 
                      240, 240, 240);
   }
}

void set_active_text_cell(int row, int column, Interface* interface) {
    interface->active_txt.row = row;
    interface->active_txt.column = column;
}

                      /* Text File Handling */


FILE* open_file(char *file_name) {
    FILE *input_file = fopen(file_name, "r");
    if(input_file == NULL) {
        printf("File does not exist.\n");
        make_file(file_name);
    }
    return input_file;
} 

FILE* make_file(char *file_name) {
    FILE* new_file = fopen(file_name, "w");
    if(new_file != NULL) {
        printf("New file created!\n");
    }  
    else {
        printf("Error: unable to create file!");
        exit(1);
    }
    return new_file;
}

void write_text_to_file(Interface* interface, char* file_name) {
    FILE* user_code = fopen(interface->code_file, "w");

    for(int row = 0; row < interface->editor_rows; row++) {
        for(int column = 0; column < interface->editor_columns; column++) {
            write_text_to_cell(interface, user_code, row, column); 
        }
        fputs("\n", user_code);
    }
    fclose(user_code);
}

void write_text_to_cell(Interface* interface, FILE* file_name, 
                          int row, int column) {
    if(strcmp(interface->text_editor[row][column].character, EMPTY_CELL) != 0) {
        /* This additional step solved a problem on Linux where the text editor
         would be filled with garbage on startup; causes warnings on macs */
        interface->text_editor[row][column].character[1] = '\0';
        fputs(interface->text_editor[row][column].character, file_name);
    }
}

void wipe_text_editor(Interface* interface) {
    for(int row = 0; row < interface->editor_rows; row++) {
        for(int column = 0; column < interface->editor_columns; column++) {
            strcpy(interface->text_editor[row][column].character, EMPTY_CELL);
        }
    }
}

                          /* Text Manipulation */

void Text_Editor_text_input(Interface *interface, char* text,
                                int x, int y, Coordinates active) {
    int *r = &active.row, *c = &active.column;
    if(!last_cell(active, *interface)) {
        if(strcmp(interface->text_editor[*r][*c].character, EMPTY_CELL) != 0) {
            handle_overwriting(active, interface, EMPTY_CELL);
        }
    }
    strcpy(interface->text_editor[*r][*c].character, text);

    if(!last_cell(active, *interface)) {
        SDL_SetTextInputRect(&interface->text_editor[*r][*c].next->box.rect);
        set_active_text_cell(
                          interface->text_editor[*r][*c].next->text_cell.row, 
                          interface->text_editor[*r][*c].next->text_cell.column, 
                          interface);
    }
}

void Text_Editor_keydown(Interface *interface, int key,
                             int x, int y, Coordinates active) {
    switch(key) {

        case SDLK_BACKSPACE:
            keydown_backspace(interface, active);
            break;
        case SDLK_RETURN:      
            keydown_return(interface, active);
            break;
        case SDLK_TAB:
            keydown_tab(interface, active);
            break;
        case SDLK_UP:
            keydown_up(interface, active);
            break;
        case SDLK_RIGHT: 
            keydown_right(interface, active);
            break;
        case SDLK_DOWN:
            keydown_down(interface, active);
            break;
        case SDLK_LEFT:   
            keydown_left(interface, active);
            break;
        //ctrl + k wipes the entire text editor 
        case SDLK_k:
            if(SDL_GetModState() & KMOD_CTRL) {
               wipe_text_editor(interface);
               SDL_SetTextInputRect(&interface->text_editor[0][0].box.rect);
               set_active_text_cell(0, 0, interface);
               break;
            }
    }
}

void keydown_backspace(Interface *interface, Coordinates active) {

    int *r = &active.row, *c = &active.column;
    if(first_cell(active)) {
      return;
    }
    else if(last_cell(active, *interface)) {
        strcpy(interface->text_editor[*r][*c].character, 
                 EMPTY_CELL); 
        strcpy(interface->text_editor[*r][*c].previous->character, 
                 EMPTY_CELL);
    }
    else if(strcmp(interface->text_editor[*r][*c].previous->character, 
                      EMPTY_CELL) != 0) {
        //If there's something in the previous cell          
        strcpy(interface->text_editor[*r][*c].previous->character, 
                 EMPTY_CELL);
       SDL_SetTextInputRect(&interface->text_editor[*r][*c].previous->box.rect);
       set_active_text_cell(
                      interface->text_editor[*r][*c].previous->text_cell.row, 
                      interface->text_editor[*r][*c].previous->text_cell.column, 
                      interface);
        handle_backspace(active, interface);
    }
    else {
        //If there's nothing in the previous cell
        handle_backspace(active, interface);  
    }
}

void keydown_return(Interface *interface, Coordinates active) {    
    if(bottom_row(active, *interface)) {
        return;
    }
    handle_carriage_return(active, interface);
    //move the cursor to the next line
    SDL_SetTextInputRect(&interface->text_editor[active.row + 1][0].box.rect);
    set_active_text_cell(active.row + 1, 0, interface);
}

void keydown_tab(Interface *interface, Coordinates active) {
    int *r = &active.row, *c = &active.column;
    if(SDL_GetModState() & KMOD_SHIFT) {
        if(*c <= 2) {
            return;
        }
        else {
            handle_tab(active, interface, 0);
            SDL_SetTextInputRect(
                         &interface->text_editor[*r][*c - TAB_LENGTH].box.rect);
            set_active_text_cell(*r, *c - TAB_LENGTH, interface);   
        }     
    }
    
    else {
        if(*c  >= interface->editor_columns - TAB_LENGTH) {
            if(!bottom_row(active, *interface)) {
                return;
            }
        }
        else {
            handle_tab(active, interface, 1);
            SDL_SetTextInputRect(
                         &interface->text_editor[*r][*c + TAB_LENGTH].box.rect);
            set_active_text_cell(*r, *c + TAB_LENGTH, interface);
        }
    }
}

void keydown_up(Interface *interface, Coordinates active) {
    int *r = &active.row, *c = &active.column;
    if(top_row(active)) {
        return;
    }
    SDL_SetTextInputRect(&interface->text_editor[*r - 1][*c].box.rect);
    set_active_text_cell(*r - 1, *c, interface);
}

void keydown_right(Interface *interface, Coordinates active) {
    int *r = &active.row, *c = &active.column;
    if(last_cell(active, *interface) || bottom_row(active, *interface)) {
        return;
    }       
    else if(strcmp(interface->text_editor[*r][*c].character, EMPTY_CELL) != 0) {
        if(end_column(active, *interface)) {
            SDL_SetTextInputRect(&interface->text_editor[*r + 1][0].box.rect); 
            set_active_text_cell(*r + 1, 0, interface);
        }
        else {
            SDL_SetTextInputRect(&interface->text_editor[*r][*c + 1].box.rect); 
            set_active_text_cell(*r, *c + 1, interface);
        }
    }
    else {
        find_next_active_node(&active, interface);
        SDL_SetTextInputRect(&interface->text_editor[*r][*c].box.rect);
        set_active_text_cell(*r, *c, interface);
    }
}

void keydown_down(Interface *interface, Coordinates active) {  
    int *r = &active.row, *c = &active.column; 
    if(bottom_row(active, *interface)) {
        return;
    }  
    else if(final_active_node(active, *interface)) {
        return;
    }   
    else {
        SDL_SetTextInputRect(&interface->text_editor[*r + 1][*c].box.rect);
        set_active_text_cell(*r + 1, *c, interface);
    }
}

void keydown_left(Interface *interface, Coordinates active) {
    int *r = &active.row, *c = &active.column;
    if(first_cell(active)) {
        return;
    }
                        
    if(strcmp(interface->text_editor[*r][*c].previous->character, 
                EMPTY_CELL) != 0) {

      if(start_column(active)) {
        SDL_SetTextInputRect(
           &interface->text_editor[*r-1][interface->editor_columns-1].box.rect); 
        set_active_text_cell(*r-1, interface->editor_columns-1, interface);
      }
      else {
          SDL_SetTextInputRect(&interface->text_editor[*r][*c - 1].box.rect); 
          set_active_text_cell(*r, *c - 1, interface);
      }
    }
    else {
        find_previous_active_node(&active, interface);
        SDL_SetTextInputRect(&interface->text_editor[*r][*c].box.rect);
        set_active_text_cell(*r, *c, interface);
    }
}

void find_next_active_node(Coordinates* active, Interface* interface) {

    TextNode* current = &interface->text_editor[active->row][active->column];
    while(current->next != NULL && 
            strcmp(current->character, EMPTY_CELL) == 0) {
        current = current->next;
    }
    if(current->next == NULL) {
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

    while(current->previous != NULL && 
            strcmp(current->previous->character, EMPTY_CELL) == 0) {
        current = current->previous;
    }
     
    if(current->previous == NULL) {
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
    if(current->next == NULL) {
        return 1;
    }
    current = current->next;
    while(strcmp(current->character, EMPTY_CELL) == 0 && 
            current->next != NULL) {
        current = current->next;
    }
    if(current->next == NULL) {
        return 1;
    }
    return 0;
}

/* Carriage Return (Enter) */

void handle_carriage_return(Coordinates active, Interface* interface) {
    char copy[interface->editor_columns][3];
    char move[interface->editor_columns][3];
    Coordinates cell = active;

    /* Move the active row down */
    shift_row_down(active, cell, interface, move, copy);
    /* Also move the following rows down */
    shift_rows_down_one(interface, active, cell, move, copy);
  
}

void shift_row_down(Coordinates active, Coordinates cell, Interface* interface, 
                    char move[interface->editor_columns][3], 
                    char copy[interface->editor_columns][3]) {

    hold_row_to_be_moved(interface, move, active, cell);
    hold_backup_of_next_row(interface, copy, active);

    replace_row_below(interface, active, move);
    set_row_to_empty(interface, active);
}

/* Store a backup of the active row */
void hold_row_to_be_moved(Interface* interface, 
                            char move[interface->editor_columns][3], 
                            Coordinates active, Coordinates cell) {

    for(int column = 0; column < interface->editor_columns; column++) {
        if(cell.column < interface->editor_columns) {
            strcpy(move[column], 
                   interface->text_editor[active.row][cell.column++].character);
        }
        else {
            strcpy(move[column], EMPTY_CELL);
        }
   }
}

/* Store a backup of the row below the active row */
void hold_backup_of_next_row(Interface* interface, 
                               char copy[interface->editor_columns][3], 
                               Coordinates active) {

    for(int column = 0; column < interface->editor_columns; column++) {
        strcpy(copy[column], 
                 interface->text_editor[active.row + 1][column].character);
    }
}

void replace_row_below(Interface* interface, Coordinates active, 
                         char move[interface->editor_columns][3]) {

    for(int column = 0; column < interface->editor_columns; column++) {
        strcpy(interface->text_editor[active.row + 1][column].character, 
                 move[column]);
    }
}

void set_row_to_empty(Interface* interface, Coordinates active) {

    for(int column = active.column; 
          column < interface->editor_columns; column++) {
        strcpy(interface->text_editor[active.row][column].character, 
                 EMPTY_CELL);
    }
}

void shift_rows_down_one(Interface* interface, 
                           Coordinates active, Coordinates cell, 
                           char move[interface->editor_columns][3], 
                           char copy[interface->editor_columns][3]) {

    /* For all of the rows after the active row */
    for(int row = active.row + 1; row < interface->editor_rows; row++) {
        /* Hold the row to be moved down */
        for(int column = 0; column < interface->editor_columns; column++) {
            strcpy(move[column], copy[column]);
        }
        /* Save a backup of the next row */
        for(int column = 0; column < interface->editor_columns; column++) {
            strcpy(copy[column], 
                     interface->text_editor[row + 1][column].character);
        }
        /* Copy the previous row into the next row */
        for(int column = 0; column < interface->editor_columns; column++) {
            strcpy(interface->text_editor[row + 1][column].character, 
                     move[column]);
        }
    }
}

/* Backspace */

void handle_backspace(Coordinates active, Interface* interface) {

    Coordinates cell = active;
    char copy[interface->editor_columns][3];

    /* Check whether the cells in the row (after the active column)
       contain anything: handle backspacing accordingly */
    if(!rest_of_row_empty(active, interface)) {;
        text_after_active_column(active, cell, interface, copy);
    }
    else {
        if(entire_row_empty(active.row, interface) && !top_row(active)) {
            shift_row_up(active, cell, interface, copy);
        }
    }
}

void shift_row_up(Coordinates active, Coordinates cell, Interface* interface, 
                    char copy[interface->editor_columns][3]) {

    /* Set active coordinates based upon whether the row above is empty */
    check_row_above(active, &cell, interface);
    set_active_text_cell(cell.row, cell.column, interface); 
    SDL_SetTextInputRect(
                       &interface->text_editor[cell.row][cell.column].box.rect);

    if(start_column(active) && !entire_row_empty(active.row, interface)) {
        concatenate_to_previous_text(active, cell, interface, copy);
    }

    shift_rows_back_one(active, interface);   
}

void check_row_above(Coordinates active, Coordinates* cell, 
                       Interface* interface) {
    if(entire_row_empty(active.row - 1, interface)) {
        cell->row = cell->row - 1;
        cell->column = 0;
    }
    else {
        find_previous_active_node(cell, interface);
    }
}

void text_after_active_column(Coordinates active, Coordinates cell, 
                                Interface* interface, 
                                char copy[interface->editor_columns][3]) {

    store_row_backup(active, interface, copy);

    /* If the active row is not being shifted on to the previous row, just move
       everything back by one */
    if(!start_column(active)) {
      shift_cells_back_one(active, interface, copy);
    }
    /* Otherwise, move the contents of the row up to the next line */
    else { 
      shift_row_up(active, cell, interface, copy);
    }
}

void store_row_backup(Coordinates active, Interface* interface,
                        char backup[interface->editor_columns][3]) {

    for(int column = 0; column < interface->editor_columns; column++) {
        strcpy(backup[column], 
                 interface->text_editor[active.row][column].character);
    }
}

void shift_cells_back_one(Coordinates active, Interface* interface, 
                            char backup[interface->editor_columns][3]) {

    for(int column = active.column; 
          column < interface->editor_columns; column++) {
        strcpy(interface->text_editor[active.row][column - 1].character, 
                 backup[column]);
    }  
}

void concatenate_to_previous_text(Coordinates active, Coordinates cell, 
                                    Interface* interface, 
                                    char copy[interface->editor_columns][3]) {

    for(int column = active.column; 
          column < interface->editor_columns; column++) {
        strcpy(interface->text_editor[cell.row][cell.column++].character, 
                 copy[column]);
    }  
}

void shift_rows_back_one(Coordinates active, Interface* interface) {

    for(int row = active.row; row < interface->editor_rows; row++) {
        for(int column = 0; column < interface->editor_columns; column++) {
            if(row != interface->editor_rows - 1) {
                strcpy(interface->text_editor[row][column].character, 
                         interface->text_editor[row + 1][column].character);
            }
            else {
                strcpy(interface->text_editor[row][column].character, 
                         EMPTY_CELL);
            }
        }
   }
}

/* Tab */

void handle_tab(Coordinates active, Interface* interface, int direction) {

    Coordinates cell = active;
    char copy[interface->editor_columns][3];
    int tab = 0;
    /* If tab forward (indent) */
    if(direction == 1) {
        tab = 3;
    }
    /* Otherwise, tab backward (unindent) */
    else {
        tab = -3;
    }

    /* Save a copy of the row */
    tab_save_row_backup(interface, active, cell, copy);
    add_tab_space(interface, active, tab);  
    tab_shift_row(interface, active, copy, tab);

    /* Prevents garbage from entering the end of the row when unindenting */
    if(direction != 1) {
        tab_unindent_garbage_fix(interface, active, tab);
    }
}

void tab_save_row_backup(Interface* interface, 
                           Coordinates active, Coordinates cell, 
                           char copy[interface->editor_columns][3]) {

    for(int column = active.column; 
          column < interface->editor_columns; column++) {
        strcpy(copy[column], 
                 interface->text_editor[active.row][cell.column++].character); 
    }
}

void add_tab_space(Interface* interface, Coordinates active, int tab) {

    for (int column = active.column; column < active.column + tab; column++) {
        strcpy(interface->text_editor[active.row][column].character, " ");
    }
}

void tab_shift_row(Interface* interface, Coordinates active, 
                     char copy[interface->editor_columns][3], int tab) {

    for(int column = active.column+tab; 
          column < interface->editor_columns; column++) {
       strcpy(interface->text_editor[active.row][column].character, 
                copy[column - tab]);  
    }
}

void tab_unindent_garbage_fix(Interface* interface, 
                                Coordinates active, int tab) {
    for(int column = interface->editor_columns - 1; 
          column > interface->editor_columns + tab - 1; column--) {
        strcpy(interface->text_editor[active.row][column].character, 
                 EMPTY_CELL);
    }
}

                            /* Text Overflow */

void handle_overwriting(Coordinates active, Interface* interface, 
                          char* overflow) {
    Coordinates over = active;
    TextNode* current = &interface->text_editor[active.row][active.column];
    char curr[3];
    char nxt[3];

    current = handle_initial_cell(overflow, nxt, curr, current);
  
    shuffle_rest_of_line(active, *interface, current, curr, nxt);

    if(!bottom_row(active, *interface)) {
        if (shuffle_overflow(&over, *interface, nxt)) {
            handle_overwriting(over, interface, nxt);
        }
    }
}

int text_overflow(char* overflow) {

    if(strcmp(overflow, EMPTY_CELL) != 0) {
        return 1;
    }
    return 0;
}

TextNode* handle_initial_cell(char* overflow, char* nxt, char* curr, 
                                TextNode* current) {

    //text overflow is where the current text input also affects the next line 
    //overflow is carried over recursively from the previous instance of the function
    if(text_overflow(overflow)) {
        handle_overflow(nxt, current, overflow, curr);
    }
    else {
        shuffle_active_cell(curr, current, nxt);
    }
    return current->next;
}

/* When starting out on making the text editor more complex, I decided that 
the overflow feature was one of the first problems I should tackle. 
In retrospect, I would have designed the text editor as if it had non-finite columns 
and rows. However, to properly do this requires scrolling, something which I 
did not have time to implement */

/* Essentially, overflow is the text from one line spilling over on to the next */

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
void shuffle_rest_of_line(Coordinates active, Interface interface, 
                            TextNode* current, char* curr, char* nxt) {

    int column = active.column;
    int condition = interface.editor_columns - 1;

    //since the text editor isn't scrolling, the condition for the bottom row 
    //simply drops the final column's character
    if (bottom_row(active, interface)) {
        condition -= 1;
    }

    while (column < condition) {
        column++; 
        if (strcmp(nxt, EMPTY_CELL) != 0) {
            current = current->next;
            strcpy(curr, nxt);
            strcpy(nxt, current->character);
            strcpy(current->character, curr);
        }
    }
}

int shuffle_overflow(Coordinates* over, Interface interface, char* nxt) {

    over->row += 1;
    over->column = 0;
    if(strcmp(interface.text_editor[over->row][0].character, EMPTY_CELL) != 0) {
        if(strcmp(nxt, EMPTY_CELL) != 0) {           
            return 1;
        }
    }
    return 0;
}

                        /* Helper Functions */

int top_row(Coordinates active) {
    if(active.row == 0) {
        return 1;
    }
    return 0;
}

int bottom_row(Coordinates active, Interface interface) {
    if(active.row == interface.editor_rows - 1) {
        return 1;
    }
    return 0;
}

int start_column(Coordinates active) {
    if(active.column == 0) {
        return 1;
    }
    return 0;
}

int end_column(Coordinates active, Interface interface) {
    if(active.column == interface.editor_columns - 1) {
        return 1;
    }
    return 0;
}

int first_cell(Coordinates active) {
    if(top_row(active) && start_column(active)) {
        return 1;
    }
    return 0;
}

int last_cell(Coordinates active, Interface interface) {
    if(bottom_row(active, interface) && end_column(active, interface)){
        return 1;
    }
    return 0;
}

int rest_of_row_empty(Coordinates active, Interface* interface) {

    for(int column = active.column; 
          column < interface->editor_columns; column++) {
        if(strcmp(interface->text_editor[active.row][column].character, 
                    EMPTY_CELL) != 0) {
            return 0;
        }
    }
    return 1;
}

int entire_row_empty(int row, Interface* interface) {

    for(int column = 0; column < interface->editor_columns; column++) {
        if(strcmp(interface->text_editor[row][column].character, 
                    EMPTY_CELL) != 0) {
            return 0;
        }
    }
    return 1;
}

int is_empty_cell(char* character) {

    if(strcmp(character, EMPTY_CELL) == 0) {
        return 1;
    }
    return 0;
}

void mouse_move_to_cell(Interface* interface, int mouse_x, int mouse_y) {
    for(int row = 0; row < interface->editor_rows; row++) {
        for(int column = 0; column < interface->editor_columns; column++) {
            if(inside_cell(interface->text_editor[row][column], 
                             mouse_x, mouse_y)) {
              //click on a cell with text within? take you directly to that cell
                if(strcmp(interface->text_editor[row][column].character, 
                            EMPTY_CELL) != 0) {
                    SDL_SetTextInputRect(
                      &interface->text_editor[row][column-TAB_LENGTH].box.rect);
                    set_active_text_cell(row, column, interface);  
                }
                //click on a line? take to prev live cell on that row
                else {
                    find_prev_cell_on_row(&interface->text_editor[row][column], 
                                             interface);
                }
            }
        }
    }
}

void find_prev_cell_on_row(TextNode* current, Interface* interface) {
    while(current->text_cell.column != 0 && 
            strcmp(current->previous->character, EMPTY_CELL) == 0) {
        current = current->previous;  
    }
    int r = current->text_cell.row;
    int c = current->text_cell.column;
    SDL_SetTextInputRect(&interface->text_editor[r][c].box.rect);
    set_active_text_cell(r, c, interface);  
}

void console_text_editor(Interface interface) {
    int row, col;
    row = col = 0;
    for(row = 0; row <= interface.editor_rows; row++) {
        for(col = 0; col < interface.editor_columns; col++) {
            printf("%s", interface.text_editor[row][col].character);
        }
        printf("\n");
    }
    printf("\n");
}
