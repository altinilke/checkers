/*
 ============================================================================
 Name        : checkers.c
 Author      : altin
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define A_size  11
#define I_size  14
int A[A_size][A_size];
int X[I_size]        = 		{	0,  0, 	1,	1,  2,  2,  3,  4,	5,  5,	6, 	7,	8,	9,	};
int Y[I_size]        = 		{	8,  3,  2,  4,  0,  6,  4,  1, 	2,  6,  4,	6,	7,	8,	};
int point[I_size]    = 		{	10,	1,  10, 1,  1,  10, 1,	10,	10,  10, 1,	1,	1,	1,	};

int y_step(int* y_pos, int curr_x)
{
    int points = 0;

    for(int y=*y_pos+1; y<A_size-1; y++)
     {
        if((A[curr_x][y] != 0)&&(A[curr_x][y+1] == 0))
        {
            points = A[curr_x][y];
            *y_pos = y+1;
            break;
        }
     }
     return points;
}

int y_step_2(int* y_pos, int curr_x, int last_y)
{
    int found = 0;
    int points = 0;
    int points_i = 0;
    int y_i;
    int exit_flag = 0;
    int search_y;

    for(int y=*y_pos+1; y<A_size-1; y++)
     {
        if((A[curr_x][y] != 0)&&(A[curr_x][y+1] == 0))
        {
        	points_i = A[curr_x][y];
        	y_i = y+1;
        	search_y = y;
        	if(y < last_y)
        		search_y = last_y;
            for(int i = search_y+1; i < A_size; i++)
            {
                //printf("\n A[%d][%d]:%d",curr_x,i,A[curr_x][i]);
                if(A[curr_x][i] != 0)
                {
                    //printf("\n Emergency! A[%d][%d]:%d",curr_x,i,A[curr_x][i]);
                    exit_flag = 1;
                    break;
                }
                for(int j = curr_x+1; j < A_size; j++)
                {
                    //printf("\n curr_x:%d x:%d y:%d",curr_x,j,i);
                    if(A[j][i] > 0)
                    {
                        points = A[curr_x][y];
                        //printf("\n curr_x:%d x:%d y:%d points: %d A[%d][%d]:%d",curr_x,j,i,points,j,i,A[j][i]);
                        exit_flag = 1;
                        found = 1;
                        *y_pos = i;
                        break;
                    }
                }
                if(exit_flag)
                {
                    break;
                }
            }
            if(exit_flag)
            {
                exit_flag = 0;
                break;
            }
        }
     }
    if((points_i > 0) && (found == 0) && (last_y == 0))
    {
    	points = points_i;
    	*y_pos = y_i;
    }
     return points;
}

int x_step(int* x_pos, int curr_y)
{
    int points = 0;

    for(int x=*x_pos+1; x<A_size-1; x++)
     {
        if((A[x][curr_y] != 0)&&(A[x+1][curr_y] == 0))
        {
            points = A[x][curr_y];
            *x_pos = x+1;
            break;
        }
     }
    return points;
}

int x_step_2(int* x_pos, int curr_y, int last_x)
{
    int found = 0;
    int points = 0;
    int points_i = 0;
    int x_i;
    int exit_flag = 0;
    int search_x;

    for(int x=*x_pos+1; x<A_size-1; x++)
     {
        if((A[x][curr_y] != 0)&&(A[x+1][curr_y] == 0))
        {
        	points_i = A[x][curr_y];
        	x_i = x+1;
        	search_x = x;
        	if(x < last_x)
        		search_x = last_x;
            for(int i = search_x+1; i < A_size; i++)
            {
                //printf("\n A[%d][%d]:%d",curr_x,i,A[curr_x][i]);
                if(A[i][curr_y] != 0)
                {
                    //printf("\n Emergency! A[%d][%d]:%d",curr_x,i,A[curr_x][i]);
                    exit_flag = 1;
                    break;
                }
                for(int j = curr_y+1; j < A_size; j++)
                {
                    //printf("\n curr_x:%d x:%d y:%d",curr_x,j,i);
                    if(A[i][j] > 0)
                    {
                        points = A[x][curr_y];
                        //printf("\n curr_x:%d x:%d y:%d points: %d A[%d][%d]:%d",curr_x,j,i,points,j,i,A[j][i]);
                        exit_flag = 1;
                        found = 1;
                        *x_pos = i;
                        break;
                    }
                }
                if(exit_flag)
                {
                    break;
                }
            }
            if(exit_flag)
            {
                exit_flag = 0;
                break;
            }
        }
     }
    if((points_i > 0) && (found == 0) && (last_x == 0))
    {
    	points = points_i;
    	*x_pos = x_i;
    }
     return points;
}


int solution(int x_pos, int y_pos)
{
    int points;
    int x_new, y_new;
    int x_found, y_found;
    static int level = 0;
    static int total_points = 0;
    static int max_points = 0;
    level++;
    printf("\n Entry to Level %d at [%d,%d] with points: %d ",level,x_pos,y_pos,total_points);

    y_found = 0;
    for(int i = 0; i < (A_size - y_pos); i++)
	{
		y_new = y_pos;
		printf("\n Run y step at [%d,%d] with y_found: %d",x_pos,y_new,y_found);
		points = y_step_2(&y_new,x_pos,y_found);
		if(points > 0)
		 {
			y_found = y_new;
			total_points += points;
			printf("\n After y step at [%d,%d] with y_found: %d",x_pos,y_new,y_found);
			printf("\n Y step caused entry to Level %d Points: %d",level+1,total_points);
			if(max_points < total_points)
				max_points = total_points;
			solution(x_pos, y_new);
			printf("\n Re-entry after y step caused solution Level: %d at [%d,%d]",level,x_pos,y_pos);
			total_points -= points;
		 }
		else
		{
			printf("\n After y step at [%d,%d] with y_found: %d",x_pos,y_new,y_found);
			break;
		}
	}

    x_found = 0;
    for(int i = 0; i < (A_size - y_pos); i++)
	{
		x_new = x_pos;
		printf("\n Run x step at [%d,%d] with x_found: %d",x_new,y_pos,x_found);
		points = x_step_2(&x_new,y_pos,x_found);
		if(points > 0)
		 {
			x_found = x_new;
			total_points += points;
			printf("\n After x step at [%d,%d] with x_found: %d",x_new,y_pos,x_found);
			printf("\n X step caused entry to Level %d Points: %d",level+1,total_points);
			if(max_points < total_points)
				max_points = total_points;
			solution(x_new, y_pos);
			printf("\n Re-entry after x step caused solution Level: %d at [%d,%d]",level,x_pos,y_pos);
			total_points -= points;
		 }
		else
		{
			printf("\n After x step at [%d,%d] with x_found: %d",x_new,y_pos,x_found);
			break;
		}
	}

    printf("\n Exit from Level %d at [%d,%d] Points: %d",level,x_pos,y_pos,total_points);
    level--;
    return max_points;
}


int main()
{
	setbuf(stdout, NULL);
    int y_pos=0;
    int x_pos=0;
    int result;

    for (int i = 0; i < A_size; i++)
    {
        for (int j = 0; j < A_size; j++)
        {
            A[i][j] = 0;
        }
    }

    for (int k = 0; k < I_size; k++)
    {
        A[X[k]][Y[k]] = point[k];
    }


    for (int j = A_size -1; j >= 0; j--)
    {
    	printf("\n");

        for (int i = 0; i < A_size; i++)
        {
            printf("%3d ",A[i][j]);
        }
    }

    result = solution(x_pos, y_pos);
    printf("\n Highest Possible Point: %d ",result);
    return 0;
}
