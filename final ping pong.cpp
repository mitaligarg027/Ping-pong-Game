#include<stdio.h>
#include<conio.h>
#include<iostream>
#include<time.h>
#include<windows.h>
#include<stdlib.h>
#include<direct.h>
#include<graphics.h>
#include<math.h>
using namespace std;

int width=800,height=600,page=0,r=6,leftscore=0,rightscore=0;
int speed=15,paddlespeed=20;
int boun=30;//boundary


//starting screen
void setup()
{
    initwindow(width,height,"");
    //boundary
    setfillstyle(1,8);  //solid fill,dark gray color
     bar(0,0,width,boun);  //top bar
     bar(0,0,boun,height);//left bar
     bar(0,height,width,height-boun);//bottom bar
     bar(width-boun,boun,width,height+boun);//right bar
    settextstyle(DEFAULT_FONT,HORIZ_DIR,6);//6=charsize
     outtextxy(100,height/2,"LETS BEGIN:");
     delay(2000);
      srand(NULL);
}
//ending screen showing final result
void end()
    {
        initwindow(width,height,"");
    setfillstyle(1,12);
    bar(0,0,width,boun);
     bar(0,0,boun,height);
     bar(0,height,width,height-boun);
     bar(width-boun,boun,width,height+boun);
    if(leftscore>rightscore)
    {
        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
        outtextxy(100,height/2,"Player 1 wins");
    }
    else if(leftscore<rightscore)
        {

            settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
        outtextxy(100,height/2-100,"Player 2 wins");


        }
        delay(2000);
        exit(1);
    }


//score
void scoreshow()
{
    char arr[50];
sprintf(arr,"player 1 : %d/10",leftscore);  //stores score
char arr1[50];
sprintf(arr1,"player 2 : %d/10",rightscore);
setfillstyle(1,2);
settextstyle(DEFAULT_FONT,HORIZ_DIR,-1);
outtextxy(50,50,arr);  //print
outtextxy(width-200,50,arr1);


settextstyle(DEFAULT_FONT,HORIZ_DIR,8);
char w1[50],w2[50];
sprintf(w1,"%d",leftscore);
outtextxy(width/4-10,height/2,w1);
sprintf(w2,"%d",rightscore);
outtextxy(width/4+width/2+10,height/2,w2);


}

    //paddle class
    class paddle
    {
        public:
        float x=10,y=height/2-60,w=x+10,h=height/2+60;
        paddle(boolean left)
        {
            if(left)
            {
            x=5;
            }
            else
            {
                x=width-5;
            }
        }

        void move(float steps)
        {

int diff=h-y;//gets paddle
        y+=2*steps;
        h+=2*steps;

        if(h<=diff)
        {
         y= y-(2*steps);
        h= h-(2*steps);
        }
        else if(h > height)
        {
         y= y- (2*steps);
        h= h-(2*steps);
        }
    }
    void show()  //for paddle 1
    {

        setfillstyle(1,15);
        bar(x,y,w,h);
    }
    void show1()//for paddle 2
    {
         setfillstyle(1,15);
         float r1=width-20;
        bar(r1,y,r1+15,h);

    }
    };
    int random(int min ,int max)
{
    int distance,anyRandom,x;
    distance = max-min;
    anyRandom = rand();

    x = anyRandom % distance;
    return(x+min);
}
//ball
class Puck
{
    public:
    float x=width/2,y=height/2,xspeed,yspeed;

Puck()
{
    reset();


}
void update()
{
    x=x+xspeed;
    y=y+yspeed;
}
void reset()
{
    x=width/2;
    y=height/2;
//    srand(time(NULL));

    float e =random(45,-135);
    float angle= 0.017453*e;  //1deg=0.017453 rad
    if( e == 180 || e == 0)
    {
    float e =random(45,-135);
    float angle= 0.017453*e;
    }
    xspeed=speed*cos(angle);
    yspeed= speed* sin (angle);


}
void edges()
{
    if(y-r-5<5  || y+r+r>height-5)
    {

        yspeed *= -1;
    }

    if(x+r> width )
    {
        leftscore++;
        reset();
    }
    if(x-r <0)
    {
        rightscore++;
        reset();
    }


}
void show()
{
    setfillstyle(1,12);
    fillellipse(x,y,r*2,r*2);
     delay(20);
}


};
int main()
{
    setup();
    srand(time(NULL));
    Puck puck;
//Paddle object;
paddle left(true);
paddle right(false);
int flag=0;
for(;;)
{

    setactivepage(page);
    setvisualpage(1-page);
    cleardevice();

    //centre line
    setfillstyle(9,15);
    bar(width/2-10,0,width/2+10,height);

    left.show();
    right.show1();

     scoreshow();



     puck.update();
        puck.edges();
      puck.show();

       if(GetAsyncKeyState('A'))
      {
          left.move(-paddlespeed);
      }
      else if (GetAsyncKeyState('Z'))
      {
          left.move(paddlespeed);
      }


      if(GetAsyncKeyState(VK_UP))
      {
          right.move(-paddlespeed);
      }
      else if (GetAsyncKeyState(VK_DOWN))
      {
          right.move(paddlespeed);
      }

      //right segment
for(int n=1;n<=8;n++)
{

    int seg=0;
    int diff=right.h-right.y;
    int q=diff/8;  //height of each segment
    int a=puck.y;
    int b=right.y+(n*q);
    int c=right.y+((n+1)*q);
    if((puck.x>=width-40) && ((a>=b )&& (a<=c)))
       {

           seg=n+1;
           int t=0;
             if (seg ==1 ) {t = -135;}
                else if (seg == 2) {t = -150;}
                 else if (seg == 3) {t = -165;}
                  else if (seg == 4) {t = 180;}
                   else if (seg == 5) {t = 180;}
                    else if (seg == 6) {t = 165;}
                     else if (seg == 7) {t = 150;}
                      else if (seg == 8) {t = 135;}//- ka farak
                int angle = 0.017453 *t;  //1 degree= 0.017453radians
    puck.xspeed=(-1)*speed*cos(angle);
    puck.yspeed= (-1)*speed* sin (angle);
                puck.xspeed *= -1;
                break;
       }

}
//left segment
for(int n=1;n<=8;n++)
{

    int seg=0;
    int diff=left.h-left.y;
    int q=diff/8;  //height of each segment
    int a=puck.y;
    int b=left.y+(n*q);
    int c=left.y+((n+1)*q);
    if((puck.x<=40) && ((a>=b) && (a<=c)))
       {

           seg=n+1;
           int t=0;
           if (seg ==1 ) {t = -135;}
                else if (seg == 2) {t = -150;}
                 else if (seg == 3) {t = -165;}
                  else if (seg == 4) {t = -180;}
                   else if (seg == 5) {t = 180;}
                    else if (seg == 6) {t = 165;}
                     else if (seg == 7) {t = 150;}
                      else if (seg == 8) {t = 135;}
                int angle = 0.017453 *t;  //1 degree= 0.017453radians
    puck.xspeed=speed*cos(angle);
    puck.yspeed= speed* sin (angle);
                puck.xspeed *= -1;
                break;
}}
if(leftscore==10 || rightscore==10)
{
cleardevice();
    end();
}
    page=1-page;
}
exit(1);
}
