#include "draw.h"

char *numToString(int num) {
  char *result = "0000000";
  int k, n;
  int i = 0;
  if (num == 0) {
    result[0] = '0';
    result[1] = '\0';
    return result;
  }
  while (num > 0) {
    result[i++] = num % 10 + 48;
    num /= 10;
  }
  result[i] = '\0';
  i--;
  for (n = i; i > n / 2; i--)
  {
    k = result[i];
    result[i] = result[n - i];
    result[n - i] = k;
  }
  return result;
}

void drawWelcomePage(int smode)
{
   int driver=0, mode=VESA_1024x768x8bit;
   initgraph(&driver, &mode, "");
   cleardevice();
   load_8bit_bmp(60,0,"pacman.bmp");
  switch(smode)
  {
    case 0:
    {
          setcolor(0xC0);
          rectangle(220,200,340,230);
          _fill_color=0xC0;
          floodfill(290,215,0xC0);
          setcolor(WHITE);
          outtextxy(230,210,"Stupid Enemy");
      setcolor(WHITE);
      outtextxy(230,300,"Average Enemy");
      outtextxy(230,390,"Cruel Enemy");
      break;
    }
    case 1:
    {
      setcolor(0xC0);
          rectangle(220,290,340,320);
          _fill_color=0xC0;
          floodfill(290,300,0xC0);
          setcolor(WHITE);
          outtextxy(230,300,"Average Enemy");
      setcolor(WHITE);
      outtextxy(230,210,"Stupid Enemy");
      outtextxy(230,390,"Cruel Enemy");
      break;
    }
    case 2:
    {
      setcolor(0xC0);
          rectangle(220,380,340,410);
          _fill_color=0xC0;
          floodfill(290,400,0xC0);
          setcolor(WHITE);
          outtextxy(230,390,"Cruel Enemy");
      setcolor(WHITE);
      outtextxy(230,210,"Stupid Enemy");
      outtextxy(230,300,"Average Enemy");
    }
    
  }
}

void initMap(int map[32][28])
{
   int i , j;
   cleardevice();
   for(j=0;j<28;j++)
   {
    setcolor(EGA_BLUE);
    line(10+j*UNIT,10,10+j*UNIT+UNIT,10);
    line(10+j*UNIT,10+640,10+j*UNIT+UNIT,10+640);
   }
   //上下边界线
   
   for(i=0;i<32;i++)
    for(j=0;j<28;j++)
    {
      if((map[i][j]==0||map[i][j]==4)&&(map[i][j+1]==1||map[i][j+1]==2||map[i][j+1]==3)&&(map[i+1][j]==0||map[i+1][j]==4)&&(map[i-1][j]==0||map[i-1][j]==4))
        line((j+1)*UNIT,10+i*UNIT,(j+1)*UNIT,10+(i+1)*UNIT);
    
   //豆左竖线
   
        else if((map[i][j]==0||map[i][j]==4)&&(map[i][j-1]==1||map[i][j-1]==2||map[i][j-1]==3)&&(map[i+1][j]==0||map[i+1][j]==4)&&(map[i-1][j]==0||map[i-1][j]==4))
        line(20+j*UNIT,10+i*UNIT,20+j*UNIT,10+(i+1)*UNIT);
   //豆右竖线
   
      else if((map[i][j]==0||map[i][j]==4)&&(map[i+1][j]==1||map[i+1][j]==2||map[i+1][j]==3)&&(map[i][j+1]==0||map[i][j+1]==4)&&(map[i][j-1]==0||map[i][j-1]==4))
        line(10+j*UNIT,20+i*UNIT,10+(j+1)*UNIT,20+i*UNIT);
   //豆上横线
  
      else if((map[i][j]==0||map[i][j]==4)&&(map[i-1][j]==1||map[i-1][j]==2||map[i-1][j]==3)&&(map[i][j+1]==0||map[i][j+1]==4)&&(map[i][j-1]==0||map[i][j-1]==4))
        line(10+j*UNIT,20+i*UNIT,10+(j+1)*UNIT,20+i*UNIT);
   //豆下横线

      else if((map[i][j]==0||map[i][j]==4)&&(map[i-1][j]==1||map[i-1][j]==2||map[i-1][j]==3)&&(map[i][j+1]==1||map[i][j+1]==2||map[i][j+1]==3))
      {
        line(10+j*UNIT,20+i*UNIT,20+j*UNIT,20+i*UNIT);
        line(20+j*UNIT,20+i*UNIT,20+j*UNIT,30+i*UNIT);  
      }
   //右上拐角1
   
      else if((map[i][j]==0||map[i][j]==4)&&(map[i+1][j]==1||map[i+1][j]==2||map[i+1][j]==3)&&(map[i][j+1]==1||map[i][j+1]==2||map[i][j+1]==3))
      {
        line(10+j*UNIT,20+i*UNIT,20+j*UNIT,20+i*UNIT);
        line(20+j*UNIT,20+i*UNIT,20+j*UNIT,10+i*UNIT);  
      }
   //右下拐角1 
   
      else if((map[i][j]==0||map[i][j]==4)&&(map[i-1][j]==1||map[i-1][j]==2||map[i-1][j]==3)&&(map[i][j-1]==1||map[i][j-1]==2||map[i][j-1]==3))
      {
        line(20+j*UNIT,20+i*UNIT,30+j*UNIT,20+i*UNIT);
        line(20+j*UNIT,20+i*UNIT,20+j*UNIT,30+i*UNIT);  
      }
   //左上拐角1
   
      else if((map[i][j]==0||map[i][j]==4)&&(map[i+1][j]==1||map[i+1][j]==2||map[i+1][j]==3)&&(map[i][j-1]==1||map[i][j-1]==2||map[i][j-1]==3))
      {
        line(20+j*UNIT,20+i*UNIT,20+j*UNIT,10+i*UNIT);
        line(20+j*UNIT,20+i*UNIT,30+j*UNIT,20+i*UNIT);  
      } 
   //左下拐角1
   
      else if((map[i][j]==0||map[i][j]==4)&&(map[i+1][j]==0||map[i+1][j]==4)&&(map[i][j-1]==0||map[i][j-1]==4)&&(map[i+1][j-1]==1||map[i+1][j-1]==2||map[i+1][j-1]==3))
      {
        line(20+j*UNIT,20+i*UNIT,10+j*UNIT,20+i*UNIT);
        line(20+j*UNIT,20+i*UNIT,20+j*UNIT,30+i*UNIT);  
      } 
   //右上拐角2

      else if((map[i][j]==0||map[i][j]==4)&&(map[i-1][j]==0||map[i-1][j]==4)&&(map[i][j-1]==0||map[i][j-1]==4)&&(map[i-1][j-1]==1||map[i-1][j-1]==2||map[i-1][j-1]==3))
      {
        line(20+j*UNIT,20+i*UNIT,20+j*UNIT,10+i*UNIT);
        line(20+j*UNIT,20+i*UNIT,10+j*UNIT,20+i*UNIT);  
      } 
   //右下拐角2
  
      else if((map[i][j]==0||map[i][j]==4)&&(map[i+1][j]==0||map[i+1][j]==4)&&(map[i][j+1]==0||map[i][j+1]==4)&&(map[i+1][j+1]==1||map[i+1][j+1]==2||map[i+1][j+1]==3))
      {
        line(20+j*UNIT,20+i*UNIT,30+j*UNIT,20+i*UNIT);
        line(20+j*UNIT,20+i*UNIT,20+j*UNIT,30+i*UNIT);  
      } 
   //左上拐角2
   
      else if((map[i][j]==0||map[i][j]==4)&&(map[i-1][j]==0||map[i-1][j]==4)&&(map[i][j+1]==0||map[i][j+1]==4)&&(map[i-1][j+1]==1||map[i-1][j+1]==2||map[i-1][j+1]==3))
      {
        line(20+j*UNIT,20+i*UNIT,20+j*UNIT,10+i*UNIT);
        line(20+j*UNIT,20+i*UNIT,30+j*UNIT,20+i*UNIT);  
      } 
   //左下拐角2
   }
   for(i=0;i<32;i++)
    for(j=0;j<28;j++)
    {
      if(map[i][j]==1)
      {
      setcolor(EGA_YELLOW);
      circle(10+j*UNIT+10,10+i*UNIT+10,2);
        floodfill(10+j*UNIT+10,10+i*UNIT+10,EGA_YELLOW);
        }
        
        else if(map[i][j]==3)
        {
        setcolor(EGA_YELLOW);
      circle(10+j*UNIT+10,10+i*UNIT+10,8);
        floodfill(10+j*UNIT+10,10+i*UNIT+10,EGA_YELLOW);
        }
    }
    for(i=13,j=0;j<28;j++)
      if(map[i][j]==4)
      {   
        setcolor(MAGENTA);
        line(10+j*UNIT,20+i*UNIT,10+(j+1)*UNIT,20+i*UNIT);
      }

}

void drawInfo(int score, int up)
{
   setcolor(EGA_BLACK);
   _fill_color = BLACK;
   bar(0,0,200,20);
   setcolor(GREEN);
   settextstyle(1, 0, 6);
   outtextxy(0, 3, "===== Score = ");
   outtextxy(120, 3, numToString(score));
   outtextxy(160, 3, "UP = ");
   switch(up)
   {
      case 1:
      {
         setcolor(YELLOW);
         circle(260,20,14);
         _fill_color=YELLOW;
         floodfill(260,20,YELLOW);
         setcolor(EGA_BLACK);
         ellipse(260,20,-45,45,14,14);
         line(260,20,260+14*cos((45)*PI/180),20+14*sin((-45)*PI/180));
         line(260,20,260+14*cos((45)*PI/180),20+14*sin((45)*PI/180));
         _fill_color=EGA_BLACK;
         floodfill(260+10,20,EGA_BLACK);
         break;

      }
      case 2:
      {
         setcolor(YELLOW);
         circle(260,20,14);
         _fill_color=YELLOW;
         floodfill(260,20,YELLOW);
         setcolor(EGA_BLACK);
         ellipse(260,20,-45,45,14,14);
         line(260,20,260+14*cos((45)*PI/180),20+14*sin((-45)*PI/180));
         line(260,20,260+14*cos((45)*PI/180),20+14*sin((45)*PI/180));
         _fill_color=EGA_BLACK;
         floodfill(260+10,20,EGA_BLACK);
         setcolor(YELLOW);
         circle(300,20,14);
         _fill_color=YELLOW;
         floodfill(300,20,YELLOW);
         setcolor(EGA_BLACK);
         ellipse(300,20,-45,45,14,14);
         line(300,20,300+14*cos((45)*PI/180),20+14*sin((-45)*PI/180));
         line(300,20,300+14*cos((45)*PI/180),20+14*sin((45)*PI/180));
         _fill_color=EGA_BLACK;
         floodfill(300+10,20,EGA_BLACK);
         break;
      }
   }
}

void drawPacman(int x, int y, int direct)
{
   int beta=45;
   static n=-1;
   setcolor(YELLOW);
   circle(x,y,14);
   _fill_color=YELLOW;
   floodfill(x,y,YELLOW);
   n++;
   n=n%30;
   switch(direct)
   {
   case 0:
   {
   setcolor(EGA_BLACK);
   ellipse(x,y,beta+1.5*n,beta+90-1.5*n,14,14);
   line(x,y,x+14*cos((beta+1.5*n)*PI/180),y-14*sin((beta+1.5*n)*PI/180));
   line(x,y,x+14*cos((beta+90-1.5*n)*PI/180),y-14*sin((beta+90-1.5*n)*PI/180));
   _fill_color=EGA_BLACK;
   floodfill(x,y-10,EGA_BLACK);
   break;
   } 
   case 1:
   {
   setcolor(EGA_BLACK);
   ellipse(x,y,-beta-1.5*n,-beta-90+1.5*n,14,14);
   line(x,y,x+14*cos((-beta-1.5*n)*PI/180),y-14*sin((-beta-1.5*n)*PI/180));
   line(x,y,x+14*cos((-beta-90+1.5*n)*PI/180),y-14*sin((-beta-90+1.5*n)*PI/180));
   _fill_color=EGA_BLACK;
   floodfill(x,y+10,EGA_BLACK);
   break;
   } 
   case 2:
   {
   setcolor(EGA_BLACK);
   ellipse(x,y,-(beta-n*1.5)+180,(beta-n*1.5)+180,14,14);
   line(x,y,x+14*cos((-(beta-n*1.5)+180)*PI/180),y+14*sin((-(beta-n*1.5)+180)*PI/180));
   line(x,y,x+14*cos((beta+180-n*1.5)*PI/180),y+14*sin((beta+180-n*1.5)*PI/180));
   _fill_color=EGA_BLACK;
   floodfill(x-10,y,EGA_BLACK);
   break;
   } 
   case 3:
   {
   setcolor(EGA_BLACK);
   ellipse(x,y,-(beta-n*1.5),(beta-n*1.5),14,14);
   line(x,y,x+14*cos(-(beta-n*1.5)*PI/180),y+14*sin(-(beta-n*1.5)*PI/180));
   line(x,y,x+14*cos((beta-n*1.5)*PI/180),y+14*sin((beta-n*1.5)*PI/180));
   _fill_color=EGA_BLACK;
   floodfill(x+10,y,EGA_BLACK);
   break;
   } 
   }
}

void clearPerson(int map[32][28], int x, int y)
{
  int i , j;
  setcolor(BLACK);
  _fill_color=BLACK;
  bar((x-1)*UNIT,(y-1)*UNIT,(x+2)*UNIT,(y+2)*UNIT);
  setcolor(EGA_BLUE);
        for(i=y-1;i<=y+1;i++)
     for(j=x-1;j<=x+1;j++)
    {
        if((map[i][j]==0||map[i][j]==4)&&(map[i][j+1]==1||map[i][j+1]==2||map[i][j+1]==3)&&(map[i+1][j]==0||map[i+1][j]==4)&&(map[i-1][j]==0||map[i-1][j]==4))
        line((j+1)*UNIT,10+i*UNIT,(j+1)*UNIT,10+(i+1)*UNIT);
    
   //豆左竖线
   
        else if((map[i][j]==0||map[i][j]==4)&&(map[i][j-1]==1||map[i][j-1]==2||map[i][j-1]==3)&&(map[i+1][j]==0||map[i+1][j]==4)&&(map[i-1][j]==0||map[i-1][j]==4))
        line(20+j*UNIT,10+i*UNIT,20+j*UNIT,10+(i+1)*UNIT);
   //豆右竖线
   
      else if((map[i][j]==0||map[i][j]==4)&&(map[i+1][j]==1||map[i+1][j]==2||map[i+1][j]==3)&&(map[i][j+1]==0||map[i][j+1]==4)&&(map[i][j-1]==0||map[i][j-1]==4))
        line(10+j*UNIT,20+i*UNIT,10+(j+1)*UNIT,20+i*UNIT);
   //豆上横线
  
      else if((map[i][j]==0||map[i][j]==4)&&(map[i-1][j]==1||map[i-1][j]==2||map[i-1][j]==3)&&(map[i][j+1]==0||map[i][j+1]==4)&&(map[i][j-1]==0||map[i][j-1]==4))
        line(10+j*UNIT,20+i*UNIT,10+(j+1)*UNIT,20+i*UNIT);
   //豆下横线

      else if((map[i][j]==0||map[i][j]==4)&&(map[i-1][j]==1||map[i-1][j]==2||map[i-1][j]==3)&&(map[i][j+1]==1||map[i][j+1]==2||map[i][j+1]==3))
      {
        line(10+j*UNIT,20+i*UNIT,20+j*UNIT,20+i*UNIT);
        line(20+j*UNIT,20+i*UNIT,20+j*UNIT,30+i*UNIT);  
      }
   //右上拐角1
   
      else if((map[i][j]==0||map[i][j]==4)&&(map[i+1][j]==1||map[i+1][j]==2||map[i+1][j]==3)&&(map[i][j+1]==1||map[i][j+1]==2||map[i][j+1]==3))
      {
        line(10+j*UNIT,20+i*UNIT,20+j*UNIT,20+i*UNIT);
        line(20+j*UNIT,20+i*UNIT,20+j*UNIT,10+i*UNIT);  
      }
   //右下拐角1 
   
      else if((map[i][j]==0||map[i][j]==4)&&(map[i-1][j]==1||map[i-1][j]==2||map[i-1][j]==3)&&(map[i][j-1]==1||map[i][j-1]==2||map[i][j-1]==3))
      {
        line(20+j*UNIT,20+i*UNIT,30+j*UNIT,20+i*UNIT);
        line(20+j*UNIT,20+i*UNIT,20+j*UNIT,30+i*UNIT);  
      }
   //左上拐角1
   
      else if((map[i][j]==0||map[i][j]==4)&&(map[i+1][j]==1||map[i+1][j]==2||map[i+1][j]==3)&&(map[i][j-1]==1||map[i][j-1]==2||map[i][j-1]==3))
      {
        line(20+j*UNIT,20+i*UNIT,20+j*UNIT,10+i*UNIT);
        line(20+j*UNIT,20+i*UNIT,30+j*UNIT,20+i*UNIT);  
      } 
   //左下拐角1
   
      else if((map[i][j]==0||map[i][j]==4)&&(map[i+1][j]==0||map[i+1][j]==4)&&(map[i][j-1]==0||map[i][j-1]==4)&&(map[i+1][j-1]==1||map[i+1][j-1]==2||map[i+1][j-1]==3))
      {
        line(20+j*UNIT,20+i*UNIT,10+j*UNIT,20+i*UNIT);
        line(20+j*UNIT,20+i*UNIT,20+j*UNIT,30+i*UNIT);  
      } 
   //右上拐角2

      else if((map[i][j]==0||map[i][j]==4)&&(map[i-1][j]==0||map[i-1][j]==4)&&(map[i][j-1]==0||map[i][j-1]==4)&&(map[i-1][j-1]==1||map[i-1][j-1]==2||map[i-1][j-1]==3))
      {
        line(20+j*UNIT,20+i*UNIT,20+j*UNIT,10+i*UNIT);
        line(20+j*UNIT,20+i*UNIT,10+j*UNIT,20+i*UNIT);  
      } 
   //右下拐角2
  
      else if((map[i][j]==0||map[i][j]==4)&&(map[i+1][j]==0||map[i+1][j]==4)&&(map[i][j+1]==0||map[i][j+1]==4)&&(map[i+1][j+1]==1||map[i+1][j+1]==2||map[i+1][j+1]==3))
      {
        line(20+j*UNIT,20+i*UNIT,30+j*UNIT,20+i*UNIT);
        line(20+j*UNIT,20+i*UNIT,20+j*UNIT,30+i*UNIT);  
      } 
   //左上拐角2
   
      else if((map[i][j]==0||map[i][j]==4)&&(map[i-1][j]==0||map[i-1][j]==4)&&(map[i][j+1]==0||map[i][j+1]==4)&&(map[i-1][j+1]==1||map[i-1][j+1]==2||map[i-1][j+1]==3))
      {
        line(20+j*UNIT,20+i*UNIT,20+j*UNIT,10+i*UNIT);
        line(20+j*UNIT,20+i*UNIT,30+j*UNIT,20+i*UNIT);  
      } 
   //左下拐角2
   }
   for(i=13,j=0;j<28;j++)
      if(map[i][j]==4)
      {   
        setcolor(MAGENTA);
        line(10+j*UNIT,20+i*UNIT,10+(j+1)*UNIT,20+i*UNIT);
      }
}

void drawGhost(int index, int x, int y ,int direct, int burst)
{
   static n=-1;
   int theta=60;
   if(burst==0)
   {
   n++;
   n=n%30;
   switch(index)
   {
   case 0:
   {
   setcolor(BLUE);
   ellipse(x,y,15,165,13,13);
   line(x+13*cos(15*PI/180),y-13*sin(15*PI/180),x+13*cos(15*PI/180)+13*tan(15*PI/180),y+13);
   lineto(x+10,y+12);
   lineto(x+4*tan(theta-2*n),y+16);
   lineto(x,y+12);
   lineto(x-4*tan(theta-2*n),y+16);
   lineto(x-10,y+12);
   lineto(x-13*cos(15*PI/180)-13*tan(15*PI/180),y+13);
   lineto(x-13*cos(15*PI/180),y-13*sin(15*PI/180));
   _fill_color=EGA_BLUE;
   floodfill(x+1,y,EGA_BLUE);
   break;
   }
   case 1:
   {
   setcolor(LIGHTGREEN);
   ellipse(x,y,15,165,13,13);
   line(x+13*cos(15*PI/180),y-13*sin(15*PI/180),x+13*cos(15*PI/180)+13*tan(15*PI/180),y+13);
   lineto(x+10,y+12);
   linerel(0,4);
   lineto(x,y+12);
   linerel(-10,4);
   linerel(0,-4);
   lineto(x-13*cos(15*PI/180)-13*tan(15*PI/180),y+13);
   lineto(x-13*cos(15*PI/180),y-13*sin(15*PI/180));
   _fill_color=LIGHTGREEN;
   floodfill(x+1,y,LIGHTGREEN);  
   break;
   }
   case 2:
   {
   setcolor(RED);
   ellipse(x,y,15,165,13,13);
   line(x+13*cos(15*PI/180),y-13*sin(15*PI/180),x+13*cos(15*PI/180)+13*tan(15*PI/180),y+13);
   lineto(x+10,y+12);
   linerel(0,4);
   lineto(x,y+12);
   linerel(-10,4);
   linerel(0,-4);
   lineto(x-13*cos(15*PI/180)-13*tan(15*PI/180),y+13);
   lineto(x-13*cos(15*PI/180),y-13*sin(15*PI/180));
   _fill_color=RED;
   floodfill(x+1,y,RED);  
   break; 
   }
   case 3:
   {
   setcolor(MAGENTA);
   ellipse(x,y,15,165,13,13);
   line(x+13*cos(15*PI/180),y-13*sin(15*PI/180),x+13*cos(15*PI/180)+13*tan(15*PI/180),y+13);
   lineto(x+10,y+12);
   linerel(0,4);
   lineto(x,y+12);
   linerel(-10,4);
   linerel(0,-4);
   lineto(x-13*cos(15*PI/180)-13*tan(15*PI/180),y+13);
   lineto(x-13*cos(15*PI/180),y-13*sin(15*PI/180));
   _fill_color=MAGENTA;
   floodfill(x+1,y,MAGENTA);   
   }
   break;
   }
   
   setcolor(WHITE);
   circle(x+8,y,3);
   _fill_color=WHITE;
   floodfill(x+8,y,WHITE);
   setcolor(WHITE);
   circle(x-8,y,3);
   _fill_color=WHITE;
   floodfill(x-8,y,WHITE);
   
    
   switch(direct)
   { 
     case 0:
    {
      setcolor(BLACK);
      circle(x-8,y-2,3);
      _fill_color=BLACK;
      floodfill(x-8,y-2,BLACK);
      setcolor(BLACK);
      circle(x+8,y-2,3);
      _fill_color=BLACK;
      floodfill(x+8,y-2,BLACK);
      break;
    }
     case 1:
    {
      setcolor(BLACK);
      circle(x-8,y+2,3);
      _fill_color=BLACK;
      floodfill(x-8,y+2,BLACK);
      setcolor(BLACK);
      circle(x+8,y+2,3);
      _fill_color=BLACK;
      floodfill(x+8,y+2,BLACK);
      break;
    }
     case 2:
    {
      
      setcolor(BLACK);
      circle(x-10,y,3);
      _fill_color=BLACK;
      floodfill(x-10,y,BLACK);
      setcolor(BLACK);
      circle(x+6,y,3);
      _fill_color=BLACK;
      floodfill(x+6,y,BLACK);
      break;
    }
    
      case 3:
    { 
      setcolor(BLACK);
      circle(x+10,y,3);
      _fill_color=BLACK;
      floodfill(x+10,y,BLACK);
      setcolor(BLACK);
      circle(x-6,y,3);
      _fill_color=BLACK;
      floodfill(x-6,y,BLACK);
      break;
    }
    }
 }
    else
    {
      n++;
      n=n%30;
      setcolor(LIGHTMAGENTA);
      ellipse(x,y,15,165,13,13);
      line(x+13*cos(15*PI/180),y-13*sin(15*PI/180),x+13*cos(15*PI/180)+13*tan(15*PI/180),y+13);
      lineto(x+10,y+12);
      lineto(x+4*tan(theta-2*n),y+16);
      lineto(x,y+12);
      lineto(x-4*tan(theta-2*n),y+16);
      lineto(x-10,y+12);
      lineto(x-13*cos(15*PI/180)-13*tan(15*PI/180),y+13);
      lineto(x-13*cos(15*PI/180),y-13*sin(15*PI/180));
      _fill_color=LIGHTMAGENTA;
      floodfill(x+1,y,LIGHTMAGENTA);
      setcolor(WHITE);
      line(x+10+8*cos(45),y-8*cos(45),x+10-8*cos(45),y+8*cos(45));
      line(x+10-8*cos(45),y-8*cos(45),x+10+8*cos(45),y+8*cos(45));
      line(x+10+8*cos(45),y-8*cos(45),x+10-8*cos(45),y+8*cos(45));
      line(x-10+8*cos(45),y-8*cos(45),x-10-8*cos(45),y+8*cos(45));
      line(x-10-8*cos(45),y-8*cos(45),x-10+8*cos(45),y+8*cos(45));
   

    }
   }

void gameOverPage(int score)
{
  text_mode();
  textbackground(0);
  textcolor(WHITE);
  clrscr();
  gotoxy(20,5);
  cprintf("GAME OVER");
  gotoxy(20,10);
  cprintf("score:%d",score);
  getch();

}