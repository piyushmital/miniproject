/*	
Things to do more:
	1.(**DONE) Makethe keyboard work (give wgetch a timeout equal to the delay).
	2. Randomise the direction after collision at the x side.
	3. Game over condiion to be shown.
	4.(**DONE) Color a part of the window.
	5. (**DONE)Make a box aroun the playable area.
	6.(**DONE) Fix the MAX coordinates for the bars to be played within.
*/
#include<stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include<stdlib.h>
//#define DELAY 30000 
	//void reset(int *x, int*y){
		
	int score_left = 0, score_right = 0;
	int main(int argc, char *argv[]) {
       	int end_num = 3;
	int pause_char;
	int char_l, char_r, l, m, num_y1, num_y2, color_1, color_2, center_line;
	int set = 0, stop = 0,stop_1 = 0, p_key = 0; 
	int x = 14, y = 15, a = 15, b = 15, c , d, i = -1, k = -1, j =1, e;
        int max_y = 0, max_x = 0;
        int next_x = 0;
	int next_y = 0;
	int right_bar = 0; 
        int direction1 = 1;
	int z = 1;
	char player1[16];
	char player2[16];
	int direction2 = 1, end_game = 0;
	int DELAY = 30000;
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
	init_pair(1, COLOR_BLACK, COLOR_YELLOW);
	init_pair(2, COLOR_BLACK, COLOR_YELLOW);
	curs_set(FALSE);
	//keypad input set to true
	keypad(stdscr, TRUE);
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
		for(color_1 = 5; color_1 < max_y - 4; color_1++)
			for(color_2 = 13; color_2 < max_x - 12; color_2++)
			  	mvprintw(color_1, color_2, " ");
		//score values set for left and right player
		mvprintw(max_y - 3, max_x / 2 - 10, "  %d  ", score_left/ 2);
                mvprintw(max_y - 3, max_x / 2 + 5, "  %d  ", score_right/ 2);
                mvprintw(0, 0 , "Use arrow keys and (w or s) to play");
                mvprintw(0, max_x / 2, "Press esc to stop");
                mvprintw(1, 0, "Press 'p' to pause and 'o' to resume");
                mvprintw(1, max_x / 2, "Press '1' for level down and '2' for level up"); 
		//game over conditions **STILL UNFINISHED
		if(score_left / 2 == end_num || score_right / 2 == end_num){
			mvprintw(max_y / 2, max_x / 2 - 5, "GAME OVER");
		}
		if(score_left / 2 == end_num){
			mvprintw(max_y / 2 - 1, max_x / 2 - 6, "Player 1 won");
			stop = 1;
			//	end_game = 1;
		}
		if(score_right / 2 == end_num){
			mvprintw(max_y / 2 - 1, max_x / 2 - 6, "Player 2 won");
			stop = 1;
			//end_game = 1;
		}
		if(score_left / 2 == end_num - 1 && score_right / 2 == end_num - 1)
			end_num = end_num + 1;
		if(stop_1){
			mvprintw(max_y / 2, max_x / 2 - 10, "want to save game?");
			mvprintw(max_y / 2 + 1, max_x / 2 - 10, " Press 'y' or 'n'");
		//	timeout(0);
		//	pause_char = wgetch(stdscr);
		//	if(pause_char == 'y')
		//		mvprintw(max_x / 2 - 3, max_x / 2 - 4, "yolo");	
		}
		// printing of playing bars after every iteration
		attron(A_STANDOUT);
		for(j = 1; j < 8; j++){				
                	mvprintw(  13 + i + j, a - 1, pongbar[j -1].cha);
			mvprintw(  13 + k + j, max_x - a + 1 , pongbar[j - 1].cha);
		}
		attroff(A_STANDOUT);
		if( direction1 == -1){
			//timeout used to eliminated time waited by wgetch for input
			timeout(0);
			char_l = wgetch(stdscr);
		}else{
			timeout(0);
			char_r = wgetch(stdscr);
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
			case 'p': 	//pauses game
					stop = 1;
					stop_1 = 1;
					mvprintw(max_y/2, max_x / 2 - 10, "want to save game?");
						
					break;
			case 'o':	// resumes game
					stop = 0;
					stop_1 = 0;
					break;
			case '1':	// increased delay to ease level
					if(DELAY < 35000)
						DELAY = DELAY + 1000;
					break;
			case '2':	
					if(DELAY > 15000)
						DELAY = DELAY - 1000;
					break;
			case 27 : 	
					end_game = 1;
					break;
//			case 'y': 
					
		//			break;
			default:
					break;
		}
		switch(char_r){
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
					break;
			case '1':
                                        if(DELAY < 35000)
                                                DELAY = DELAY + 1000;
                                        break;
                        case '2':
                                        if(DELAY > 15000)
                                                DELAY = DELAY - 1000;
                                        break;
			case 27 : 
					end_game = 1;
					break;
			default: 
					break;
		}
         //     mvprintw(max_y - 3, max_x / 2 - 10, "  %d  ", score_left);
        //      mvprintw(max_y - 3, max_x / 2 + 5, "  %d  ", score_right);
	//	mvprintw(0, 0 , "Use arrow keys and (w or s) to play");
	//	mvprintw(0, max_x / 2, "Press esc to stop");
		mvprintw(y, x, "O");
     		refresh();
		//delay used to increase time between every iteration in while loop
       		usleep(DELAY);
		if(!stop || !stop_1){
		//direction changed after the ball hits the wall of each edge, with the same angle
			next_x = x + direction1;
			next_y = y + direction2;
			if(next_y > (max_y -5) || next_y < 5){
			 	direction2 = direction2 * -1;
			}else{ 
			 	y = y + direction2;
			}
			if (next_x > (max_x - 15) || next_x < 15){ 
        	 	 	direction1 = direction1 * -1;
       		 	}else {
        	 	 	 x = x + direction1;
		   	}
		}	
		if(( y > (20 + i) || y < (14 + i)) && x == a){
		//	stop = 1;
		//	stop_1 = 1;
			score_right++;
	//		reset(&y, &x, &stop, &i, &j ,&k); 
		}
		if(( y > (20 + k) || y < (14 + k)) && x == max_x - a){
		//	stop = 1;
		//	stop_1 = 1;
			score_left++;
	//		reset(&y, &x, &stop, &i, &j, &k);	
		}
	//	if(next_x  == max_x - 5  || (next_y < num_y1 || next_y > num_y2)) 
		attroff(COLOR_PAIR(1));		
		if(end_game == 1)
			break;		
	}
		endwin();
}
/*if(x == a && y == 14){
	direction1 = 1;
	direction2 = 2;
}else if(x == a && y == 20){
        direction1 = 1;
        direction2 = -2;
}elseif(x == a && y == 14){
        direction1 = 1;
        direction2 = 2;
}elseif(x == a && y == 14){
        direction1 = 1;
        direction2 = 2;
}else if(x == a && y == 14){
        direction1 = 1;
        direction2 = 2;
}elseif(x == a && y == 14){
        direction1 = 1;
        direction2 = 2;
}elseif(x == a && y == 14){
        direction1 = 1;
        direction2 = 2;
}elseif(x == a && y == 14){
        direction1 = 1;
        direction2 = 2;
}*/
