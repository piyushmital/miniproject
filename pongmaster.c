#include<stdlib.h>
#include <menu.h>
#include<stdio.h>
#include<string.h>
#include<curses.h>
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4
void play_game(int);
char *choices[] = {
                        "2 Ball Game",
                        "1 Ball Game",
                        "Load Game",
                        "Highscore",
                        "Exit",
                        (char *)NULL,
                  };
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
void reset1(int *, int *, int *, int *, int *);
int main()
{	ITEM **my_items;
	int c, max_y, max_x, out_key = 1;				
	MENU *my_menu;
        WINDOW *my_menu_win, *start;
        int n_choices, i, position = 0, go_balls = 0;
	
	/* Initialize curses */
	initscr();
	start_color();
        cbreak();
        noecho();
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_YELLOW);
	getmaxyx(stdscr, max_y, max_x);
	start = newwin( max_y, max_x, 0, 0);
	wbkgd(start, COLOR_PAIR(2));
	mvwprintw(start, max_y / 2 - 1, max_x / 2 - 17, "PongMaster 2015!!!");
	mvwprintw(start, max_y / 2 + 1, max_x / 2 - 30,"Revamped  version of the classic game pong :Instructions:");
	mvwprintw(start, max_y / 2 + 3, max_x / 2 - 42,"A player gets a point if the opponent fails to hit the ball with the paddle");
	mvwprintw(start, max_y / 2 + 4, max_x / 2 - 25, "Player reaching 15 points first, wins");
	mvwprintw(start, max_y / 2 + 6, max_x / 2 - 22," Press and key to continue! ");
	wrefresh(start);
	wgetch(start);
	/* Create items */
        n_choices = ARRAY_SIZE(choices);
        my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
        for(i = 0; i < n_choices; ++i)
                my_items[i] = new_item(choices[i], NULL);

	/* Create menu */
	my_menu = new_menu((ITEM **)my_items);

	/* Create the window to be associated with the menu */
        my_menu_win = newwin(10, 40, 4,  4);
        keypad(my_menu_win, TRUE);
     
	/* Set main window and sub window */
        set_menu_win(my_menu, my_menu_win);
        set_menu_sub(my_menu, derwin(my_menu_win, 6, 38, 3, 1));

	/* Set menu mark to the string " * " */
        set_menu_mark(my_menu, " * ");

	/* Print a border around the main window and print a title */
        box(my_menu_win, 0, 0);
	print_in_middle(my_menu_win, 1, 0, 40, "Pong Master", COLOR_PAIR(2));
	mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
	mvwhline(my_menu_win, 2, 1, ACS_HLINE, 38);
	mvwaddch(my_menu_win, 2, 39, ACS_RTEE);
	refresh();
        
	/* Post the menu */
	post_menu(my_menu);
	wrefresh(my_menu_win);

	while(/*(c = wgetch(my_menu_win)) != 'q' &&*/ out_key)
	{ c = wgetch(my_menu_win);
	      switch(c)
	        {	case KEY_DOWN:
				position = position + 1;
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				position = position - 1;
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
			case 10: 
				if(position == 0){
					go_balls = 1;	
					play_game(go_balls);
				}
				if(position == 1){
					go_balls = 0;
					play_game(go_balls);
				}
				if(position == 2){
					go_balls = 2;
					play_game(go_balls);
				}	
				if(position == 4){
					out_key = 0;
				}
				
				break; 
			default: 
					break;
				
		}
                wrefresh(my_menu_win);
	}	

	/* Unpost and free all the memory taken up */
        unpost_menu(my_menu);
        free_menu(my_menu);
        for(i = 0; i < n_choices; ++i)
                free_item(my_items[i]);
	endwin();
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{	int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}

/*	
Things to do more:
	1.(**DONE) Makethe keyboard work (give wgetch a timeout equal to the delay).
	2. Randomise the direction after collision at the x side.
	3. Game over condiion to be shown.
	4.(**DONE) Color a part of the window.
	5. (**DONE)Make a box aroun the playable area.
	6.(**DONE) Fix the MAX coordinates for the bars to be played within.
*/
void play_game(int go_balls){	
	int score_left = 0, score_right = 0;
       	int end_num = 15, FINISH = 1;
	int pause_char;
	int char_l, char_r, l, m, num_y1, num_y2, color_1, color_2, center_line;
	int set = 0, stop = 0,stop_1 = 0, p_key = 0; 
	int x = 14, y = 16, a = 15, b = 15, x1 = 14, y1 = 17, c , d, i = -1, k = -1, j =1, e;
        int max_y = 0, max_x = 0;
        int next_x = 0;
	int press_e = 0;
	int next_y = 0, flag_delay = 0;
	int right_bar = 0, signal; 
        int direction1 = 1, angle_1 = 1, angle_2 = 1;
	int z = 1, press_y = 0;
	char player1[16];
	char player2[16];
	int direction2 = 1, end_game = 0;
	int dir2 = 1, dir1 = 1;
	int ang2 = 1, ang1 = 1;
	int nex_x, nex_y;
	int DELAY = 40000;
	//if(go_balls)
	//	DELAY = 30000;
	FILE *fp;
        typedef struct bar{
		char *cha;
		int num;
	}bar;
	bar pongbar[7];
	for(j = 0; j < 7; j++){
		pongbar[j].cha = "H";
		pongbar[j].num = j;
	}
	//starting with the initialization of ncurses  
	initscr();
        noecho();
       	start_color();
	//color pairs set
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	init_pair(3, COLOR_BLACK, COLOR_CYAN);
	curs_set(FALSE);
	//keypad input set to true
	keypad(stdscr, TRUE);
	bkgd(COLOR_PAIR(3));
	//max values of x axis and y axis found
        getmaxyx(stdscr, max_y, max_x);
        while(1 ) {
		clear();
		attron(COLOR_PAIR(2));
		//center line created as partition
		for(center_line = 6; center_line < max_y; center_line++)
			mvprintw( center_line, max_x / 2, " ");
		attroff(COLOR_PAIR(2));
		attron(COLOR_PAIR(1));
		//play area given a certain color
		for(color_1 = 6; color_1 < max_y - 5; color_1++)
			for(color_2 = 13; color_2 < max_x - 12; color_2++)
			  	mvprintw(color_1, color_2, " ");
		//score values set for left and right player
		box(stdscr, ACS_VLINE, ACS_HLINE);
		mvprintw(max_y - 3, max_x / 2 - 10, "  %d  ", score_left/ 2);
                mvprintw(max_y - 3, max_x / 2 + 5, "  %d  ", score_right/ 2);
                mvprintw(1, 0 , "Use arrow keys and (w or s) to play");
                mvprintw(1, max_x / 2, "Press esc to stop");
                mvprintw(0, 0, "Press 'p' to pause and 'o' to resume");
                if(go_balls == 1)
		mvprintw(0, max_x / 2, "Press '1' for level down and '2' for level up"); 
		//game over conditions **STILL UNFINISHED
		if(score_left / 2 == end_num || score_right / 2 == end_num){
			mvprintw(max_y / 2, max_x / 2 - 5, "GAME OVER");
			FINISH = 0;
		}
		if(score_left / 2 == end_num){
			mvprintw(max_y / 2 - 1, max_x / 2 - 6, "Player 1 won");
			stop = 1;
			//	end_game = 1;
		}
		if(score_right / 2 == end_num){
			mvprintw(max_y / 2 - 1, max_x / 2 - 6, "Player 2 won");
			//end_game = 1;
			stop = 1;
		}
		if(score_left / 2 == end_num - 1 && score_right / 2 == end_num - 1)
			end_num = end_num + 1;
		if(stop_1){
			mvprintw(max_y / 2, max_x / 2 - 10, "Want to save game?");
			mvprintw(max_y / 2 + 1, max_x / 2 - 10, " Press 'y' or 'n'");	
		}
		if(go_balls){
			signal = 1;
		}else
			signal = 0;
		if(press_y ){		fp = fopen("game3.txt", "w");
					fwrite(&signal, sizeof(int), 1, fp);
				     	fwrite(&stop, sizeof(int), 1, fp);
//                                      fwrite(&stop_1, sizeof(int), 1, fp);
                                        fwrite(&y, sizeof(int), 1, fp);
                                        fwrite(&x, sizeof(int), 1, fp);
                                        fwrite(&i, sizeof(int), 1, fp);
                                        fwrite(&k, sizeof(int), 1, fp);
                                        fwrite(&DELAY, sizeof(int), 1, fp);
                                        fwrite(&next_x, sizeof(int), 1, fp);
                                        fwrite(&next_y, sizeof(int), 1, fp);
                                        fwrite(&score_left, sizeof(int), 1, fp);
                                        fwrite(&score_right, sizeof(int), 1, fp);
                                        fwrite(&direction1, sizeof(int), 1, fp);
                                        fwrite(&direction2, sizeof(int), 1, fp);
					if(signal){
						fwrite(&x1, sizeof(int), 1, fp);
						fwrite(&y1, sizeof(int), 1, fp);
						fwrite(&nex_x, sizeof(int), 1, fp);
    						fwrite(&nex_y, sizeof(int), 1, fp);
    						fwrite(&dir1, sizeof(int), 1, fp);
   						fwrite(&dir2, sizeof(int), 1, fp);
   						fwrite(&go_balls, sizeof(int), 1, fp);
    					}
                                        fclose(fp);

			  mvprintw(max_y/2 , max_x /2 - 20,"            GAME SAVED           ");
                          mvprintw(max_y/2 + 1, max_x / 2 - 20, " Press 'o' to resume, esc to exit");
			
		}
		if(press_e){
					fp = fopen("game3.txt", "r");
					fread(&signal, sizeof(int), 1, fp);
					fread(&stop, sizeof(int), 1, fp);
//                       		fread(&stop_1, sizeof(int), 1, fp);
                                        fread(&y, sizeof(int), 1, fp);
                                        fread(&x, sizeof(int), 1, fp);
                                        fread(&i, sizeof(int), 1, fp);
                                        fread(&k, sizeof(int), 1, fp);
                                        fread(&DELAY, sizeof(int), 1, fp);
                                        fread(&next_x, sizeof(int), 1, fp);
                                        fread(&next_y, sizeof(int), 1, fp);
                                        fread(&score_left, sizeof(int), 1, fp);
                                        fread(&score_right, sizeof(int), 1, fp);
                                        fread(&direction1, sizeof(int), 1, fp);
                                        fread(&direction2, sizeof(int), 1, fp);
					if(signal){
                                                fread(&x1, sizeof(int), 1, fp);
                                                fread(&y1, sizeof(int), 1, fp);
                                                fread(&nex_x, sizeof(int), 1, fp);
                                                fread(&nex_y, sizeof(int), 1, fp);
                                                fread(&dir1, sizeof(int), 1, fp);
                                                fread(&dir2, sizeof(int), 1, fp);
                                                fread(&go_balls, sizeof(int), 1, fp);
                                        }
	
	//				fread(&press_y, sizeof(int), 1, fp);
                                        fclose(fp);
					press_e = 0;
		}
		// printing of playing bars after every iteration
		attron(A_STANDOUT);
		for(j = 1; j < 8 ; j++){				
                	mvprintw(  13 + i + j, a - 1, pongbar[j -1].cha);
			mvprintw(  13 + k + j, max_x - a + 1 , pongbar[j - 1].cha);
		}
		attroff(A_STANDOUT);
		if(go_balls == 1){
			timeout(0);
			char_l = wgetch(stdscr);
		}
		if(go_balls == 0 || go_balls == 2){
			if( direction1 == -1){
			//timeout used to eliminated time waited by wgetch for input
				timeout(0);
				char_l = wgetch(stdscr);
			}else{
				timeout(0);
				char_r = wgetch(stdscr);
			}
		}	
		switch(char_l)
		{	case 'w':
					if(!stop){
						i = i - 2; 
						if(i < (- 8) )
							i = (- 8);	
						attron(A_STANDOUT);
						for(j = 1; j < 8; j++)
                					mvprintw( 13 + i + j, (a - 1), pongbar[j - 1].cha);
						attroff(A_STANDOUT);
						num_y1 = 14 + i;
						num_y2 = 21 + i;
					} 
			 		break;
			case 's':	
					if(!stop){
						i = i + 2;
						if(i + 	11 > ( max_y - 15))
							i  = max_y - 26;
						attron(A_STANDOUT);
						for(j = 1; j < 8; j++)							
							mvprintw( 13 + i + j ,( a - 1), pongbar[j - 1].cha);
						attroff(A_STANDOUT);
						num_y1 = 14 + i;
						num_y2 = 21 + i;
					}
					break;
			case KEY_UP :
				if(go_balls == 1)
                                        if(!stop){
                                                k = k - 2;
                                                if(k < (- 8))
                                                        k = (- 8);
                                                attron(A_STANDOUT);
                                                for(j = 1; j < 8; j++)
                                                        mvprintw((13 + j + k), max_x - a + 1, pongbar[j - 1].cha);
                                                attroff(A_STANDOUT);
                                                num_y1 = 14 + k;
                                                num_y2 = 21 + k;
                                        }
                                        break;
                        case KEY_DOWN :
				if(go_balls == 1)
                                        if(!stop){
                                                k = k + 2;
                                                if(k + 11 > max_y - 15)
                                                        k = max_y - 26;
                                                attron(A_STANDOUT);
                                                for(j = 1; j < 8; j++)
                                                        mvprintw((13 + j + k), max_x - a + 1, pongbar[j - 1].cha);
                                                attroff(A_STANDOUT);
                                                num_y1 = 14 + k;
                                                num_y2 = 21 + k;
                                        }
                                break;
 
			case 'p': 	//pauses game
					stop = 1;
					stop_1 = 1;
					mvprintw(max_y/2, max_x / 2 - 10, "want to save game?");
						
					break;
			case 'y':		
					press_y = 1;
					break;
					
			case 'n':	
					stop = 0;
					stop_1 = 0;
					break;

			case 'o':	// resumes game
					stop = 0;
					stop_1 = 0;
					press_y = 0;
					break;
			case '1':	// increased delay to ease level
					if(DELAY < 35000)
						DELAY = DELAY + 1000;
					break;
			case '2':	
					if(DELAY > 15000)
						DELAY = DELAY - 1000;
					break;
			case 'e':	
					press_e = 1;
					break;
			case 27 : 	
					end_game = 1;
					break;
//			case 'y': 
					
		//			break;
			default:
					break;
		}
		switch(char_r ){
			case KEY_UP :	
					if(!stop){
						k = k - 2;
						if(k < (- 8))
							k = (- 8); 
						attron(A_STANDOUT);
						for(j = 1; j < 8; j++)
							mvprintw((13 + j + k), max_x - a + 1, pongbar[j - 1].cha);
						attroff(A_STANDOUT);
						num_y1 = 14 + k;
						num_y2 = 21 + k; 
					}	
					break;
			case KEY_DOWN :
					if(!stop){
						k = k + 2;
						if(k + 11 > max_y - 15)
							k = max_y - 26;
						attron(A_STANDOUT);
						for(j = 1; j < 8; j++)
							mvprintw((13 + j + k), max_x - a + 1, pongbar[j - 1].cha);
						attroff(A_STANDOUT);
						num_y1 = 14 + k;
						num_y2 = 21 + k;
					} 
				break;
			case 'p' : 	
					stop = 1;
					stop_1 = 1;
					mvprintw(max_y / 2, max_x / 2 - 10, "want to save game?");
					break;
			case 'o' : 	
					stop = 0;
					stop_1 = 0;
					press_y = 0;
					break;
			case 'n':	
					stop = 0;
					stop_1 = 0;
					break;
			case '1':
                                        if(DELAY < 35000)
                                                DELAY = DELAY + 1000;
                                        break;
			case 'e':
					press_e = 1;
					break;
                        case '2':
                                        if(DELAY > 15000)
                                                DELAY = DELAY - 1000;
                                        break;
			case 'y':
					press_y = 1;
					break;
			case 27 : 
					end_game = 1;
					break;
			default: 
					break;
		}
		mvprintw(y, x, "O");
		if(go_balls == 1)
			mvprintw(y1, x1, "O");
     		refresh();
		//delay used to increase time between every iteration in while loop
       		usleep(DELAY);
		if(!stop || !stop_1 * FINISH){

		//direction changed after the ball hits the wall of each edge, with the same angle
		//for different parts of the paddle different angles are created
			next_x = x + angle_1 * direction1;
			next_y = y + angle_2 * direction2;
			if((y == 14 + i || y == 20 + i || y == 14 + k || y == 20 + k) && (x == a || x == max_x - a)){
				angle_2 = 2;
				angle_1 = 1;
			}else if((y == 15 + i || y == 19 + i || y == 15 + k || y == 19 + k) && (x == a || x == max_x - a)){
				angle_2 = 1;
				angle_1 = 1;
			}else if((y == 16 + i || y == 18 + i || y == 16 + k || y == 18 + k) && (x == a || x == max_x - a)){
				angle_2 = 1;
				angle_1 = 2;
			}else if((y == 17 + i) && (x == a)){
				angle_2 = 0;
				angle_1 = 2;
			} 
			else if(( y == 17 + k) && ( x == max_x - a)){
				angle_2 = 0;
				angle_1 = 2;
			}else if(( y > (20 + i) || y < (14 + i) || y > (20 + k) || y < (14 + k)) && (x == a || x == max_x - a)){
				angle_2 = 1;
				angle_1 = 1;
			}
		//basic ball bouncing algorithm
			if(next_y > (max_y - 6) || next_y < 6){
			 	direction2 = direction2 * -1;
			}else{ 
			 	y = y + angle_2 * direction2;
			}
			if (next_x > (max_x - 15) || next_x < 15){ 
        	 	 	direction1 = direction1 * -1;
       		 	}else {
        	 	 	 x = x + angle_1 * direction1;
		   	}
		}
		///check condition dor 2 ball bounces
		if(go_balls == 1)
		if(!stop || !stop_1 * FINISH){
                        nex_x = x1 + ang1 * dir1;
                        nex_y = y1 + ang2 * dir2;
                        if((y1 == 14 + i || y1 == 20 + i || y1 == 14 + k || y1 == 20 + k) && (x1 == a || x1 == max_x - a)){
                                ang2 = 2;
                                ang1 = 1;
                        }else if((y1 == 15 + i || y1 == 19 + i || y1 == 15 + k || y1 == 19 + k) && (x1 == a || x1 == max_x - a)){
                                ang2 = 1;
                                ang1 = 1;
                        }else if((y1 == 16 + i || y1 == 18 + i || y1 == 16 + k || y1 == 18 + k) && (x1 == a || x1 == max_x - a)){
                                ang2 = 1;
                                ang1 = 2;
                        }else if((y1 == 17 + i ) && ( x1 == a)){
				ang2 = 0;
				ang1 = 2;
			}else if(( y1 == 17 + k) && ( x1 == max_x - a)){
                                ang2 = 0;
                                ang1 = 2;
                        }else if(( y1 > (20 + i) || y1 < (14 + i) || y1 > (20 + k) || y1 < (14 + k)) && (x1 == a || x1 == max_x - a)){
                                ang2 = 1;
                                ang1 = 1;
                        }
			if(nex_y > (max_y - 6) || nex_y < 6){
                                dir2 = dir2 * -1;
                        }else{
                                y1 = y1 + ang2 * dir2;
                        }
                        if (nex_x > (max_x - 15) || nex_x < 15){
                                dir1 = dir1 * -1;
                        }else {
                                 x1 = x1 + ang1 * dir1;
                        }
                }
		
		if(FINISH){	
			if((( y > (20 + i) || y < (14 + i)) && x == a) ||(( y1 > (20 + i) || y1 < (14 + i)) && x1 == a)){
				score_right++;
			}
			if((( y > (20 + k) || y < (14 + k)) && x == max_x - a) || (( y1 > (20 + k) || y1 < (14 + k)) && x1 == max_x - a)) {
				score_left++;
			}
		}
		attroff(COLOR_PAIR(1));		
		if(end_game == 1)
			break;		
	}	
	endwin();
	clear();
	bkgd(COLOR_PAIR(1));
	refresh();
}

 
