

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <pic32mx.h> 
#include "snake.h" //Project header file


int speed = 10000; //Higher is slower

void draw_walls(){


    int max_y = 31;
    int max_x = 127;

    int i;
    for(i = 0; i<max_y;i++){
        display[i][0] = 1;

    }

    for(i = 0; i<max_y;i++){
        display[i][127] = 1;
        
    }

    for(i = 0; i<max_x;i++){
        display[0][i] = 1;
        
    }

    for(i = 0; i<max_x;i++){
        display[31][i] = 1;
        
    }



}



void snake_grow(){

    snake_length++;


   switch (direction){

        case 'L':
           snake_array[snake_length-1].x = snake_array[snake_length-2].x +1;
           snake_array[snake_length-1].y = snake_array[snake_length-2].y;
           break;

        case 'R':
           snake_array[snake_length-1].x = snake_array[snake_length-2].x -1;
           snake_array[snake_length-1].y = snake_array[snake_length-2].y;
           break;


        case 'U':
           snake_array[snake_length-1].x = snake_array[snake_length-2].x;
           snake_array[snake_length-1].y = snake_array[snake_length-2].y+1;
           break;

        case 'D':
           snake_array[snake_length-1].x = snake_array[snake_length-2].x;
           snake_array[snake_length-1].y = snake_array[snake_length-2].y-1;
           break;

   }




}



void create_fruit(){
    //int center_x = rand()%124;
    //int center_y = rand()%32;

    int center_x = 20;
    int center_y = 10;

    fruit_array[0].x = center_x;
    fruit_array[0].y = center_y;
    
    fruit_array[1].x = center_x;
    fruit_array[1].y = center_y -1;

    fruit_array[2].x = center_x;
    fruit_array[2].y = center_y +1;

    fruit_array[3].x = center_x+1;
    fruit_array[3].y = center_y;

    fruit_array[4].x = center_x-1;
    fruit_array[4].y = center_y;

}

void draw_fruit(){

    int i;
    for(i=0;i<5;i++){
        display[fruit_array[i].y][fruit_array[i].x] = 1;

    }
}

void fruit_collision(){

    int head_x = snake_array[0].x;
    int head_y = snake_array[0].y;


    int overlap = 0;
    int i;
    for(i=0;i<5;i++){

        if((fruit_array[i].x = head_x) && (fruit_array[i].y =head_y)){
            overlap = 1;
            break;
        }
    }

    if(overlap = 1){
        score++;
        create_fruit();
    }




}



void game_restart(){

    direction = 'L';


    score = 0;

	
     
    snake_length = 15;
	int i;
	for (i=0;i<snake_length;++i){
		snake_array[i].x = 64+i;
		snake_array[i].y = 16;

	}

    create_fruit();
}



void check_head_outside_bounds(){

    int head_x = snake_array[0].x;
    int head_y = snake_array[0].y;


    if((head_x > 128) | (head_x < 0)){
        game_restart();
    
    }

    else if((head_y > 32 )| (head_y < 0)){
        game_restart();
    }

}


void check_eats_itself(){

    int head_x = snake_array[0].x;
    int head_y = snake_array[0].y;
    
    int overlap = 0;
    int i;
    for(i=2;i<snake_length;i++){

        if((snake_array[i].x == head_x) && (snake_array[i].y ==head_y)){
            overlap = 1;
        }
    }

    if(overlap == 1){
        game_restart();
    }



}



void draw_snake(){

    int i;
    for(i = 0;i<snake_length;i++){
        display[snake_array[i].y][snake_array[i].x] = 1;

    }

}


void snake_move(){


    snake_part prev = snake_array[0];


    // update following snakeparts will update to that of the preevious position of the snake part before them.

    
    int i;
    for(i=1;i<snake_length;i++){
        snake_part save_prev_position = snake_array[i];
        snake_array[i].x = prev.x;
        snake_array[i].y = prev.y;
        prev = save_prev_position;
    }

        // move head

    switch (direction){

        case 'L':
           snake_array[0].x = snake_array[0].x-1;
           break;

        case 'R':
           snake_array[0].x=snake_array[0].x+1;
           break;


        case 'U':
           snake_array[0].y=snake_array[0].y-1;
           break;

        case 'D':
           snake_array[0].y=snake_array[0].y+1;
           break;
        
    }

    

}


void get_direction(){

    int btn_value = getbtns();
    int btn_value1 = getbtn1();
    switch(btn_value){
        case 1:
        direction = 'D';
        break;

        case 2:
        direction = 'U';
        break;
        
        //4
        case 4:
        direction = 'L';
        break;


    }

    switch(btn_value1){

        case 1:
        direction = 'R';
        break;
    }


}


void game_update(){

    get_direction();
    draw_walls();
    snake_move();
    check_head_outside_bounds();
    check_eats_itself();
    fruit_collision();
    draw_fruit();
    draw_snake();


}



int getbtns(void){

int PORTD_extract = PORTD & 0x00e0;
PORTD_extract = PORTD_extract >> 5;
return PORTD_extract;

    
}


int getbtn1(void){

int PORTF_extract = PORTF & 0x0002;
PORTF_extract = PORTF_extract >> 1;
return PORTF_extract;

    
}

