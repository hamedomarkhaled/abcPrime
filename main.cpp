#include <bits/stdc++.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
using namespace std;
const double logWidth=100.0;
const double logHeight=100.0;
const int rowSize=2, columnSize=8, gridHeight=20, gridWidth=80, initHeight=95, initWidth=10, N_SIZE=20;
const int initButtonX=20 ,initButtonY=20;
double backgroundColor[3]={0.5,0.5,0.5};
double lineColor[3]={1.0,0.0,0.0};
double numberColor[3]={0.8, 0.8, 0.8};
vector <int> numbers(N_SIZE);
int _16[rowSize][columnSize], global=0, gridI, gridJ;
void init(){
    glClearColor(0.265,0.685,1.0,1.0); /**Background Color**/
    glMatrixMode(GL_PROJECTION); /**2D**/
    gluOrtho2D(0.0,logWidth,0.0,logHeight);/**Sync**/

}
string toStr(int n){
    stringstream ss; ss << n; string x; ss >>x;
    return x;
}
void printText(string s, int x, int y, double color[]){
    glColor3dv(color);
    glRasterPos2d(x, y);
    int n = (int)s.size();
    for(int i = 0; i < n; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
    glFlush();
}
int globalButton=0,originalI, originalJ, target;
void Display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    glColor3dv(backgroundColor);
    glVertex2i(initWidth,initHeight);
    glVertex2i(initWidth,initHeight-gridHeight);
    glVertex2i(initWidth+gridWidth, initHeight-gridHeight);
    glVertex2i(initWidth+gridWidth, initHeight);
    glEnd();

    glColor3dv(lineColor);
    glBegin(GL_LINES);
    for (int i = 0; i <= rowSize; i++){
        glVertex2i(initWidth,initHeight-gridHeight*i/rowSize);
        glVertex2i(initWidth+gridWidth, initHeight-gridHeight*i/rowSize);
    }
    glEnd();

    glBegin(GL_LINES);
   for(int i = 0;i<=columnSize;i++){
        glVertex2i(initWidth + gridWidth*i/columnSize, initHeight);
        glVertex2i(initWidth+gridWidth*i/columnSize, initHeight-gridHeight);
   }
   glEnd();
   /**Draw Vertical Line and 2 buttons**/
   glColor3dv(lineColor);
   glBegin(GL_LINES);
   glVertex2i(50,0), glVertex2i(50,50);
   glEnd();
   glBegin(GL_QUADS);
   for(int i = 0;i < 2;i++){

        glColor3dv(lineColor);
        glVertex2i(initButtonX + 50*i ,initButtonY);
        glVertex2i(initButtonX + 20 + 50*i ,initButtonY);
        glVertex2i(initButtonX +20 + 50*i ,initButtonY + 20);
        glVertex2i(initButtonX + 50*i ,initButtonY+20);
   }
   glEnd();
   string prime="Prime";
   string notPrime="Composite";
   printText(prime, initButtonX+5, initButtonY+10, numberColor);
   printText(notPrime, initButtonX+52, initButtonY+10, numberColor);
   /**drawing numbers into cells**/
    for(int y = initHeight-5, i = 0;i < 2;y-=10,i++){
        for(int x = initWidth+2, j = 0;j<8;x+= initWidth,j++){/****/

                if (global == 0 || i!= gridI || gridJ != j /*|| _16[i][j]!=-1*/){
                    string s = toStr(_16[i][j]);
                    if (_16[i][j] != -1)
                        printText(s, x, y, numberColor);
                    else
                        printText("done!", x, y, numberColor);
                }
        }
    }
    /**End of drawing**/

    glFlush();
    glutSwapBuffers();

}
void mouse(int button, int state, int xB , int yB){
    int xButton= xB * 1.0 / 640 *100, yButton = yB * 1.0 / 480 * 100; yButton = 100-yButton;

    if(GLUT_LEFT_BUTTON == button && GLUT_DOWN == state){
        if (!global) {
            for (int i = 0; i < rowSize && !global; i++) {
                for (int j = 0; j < columnSize && !global; j++) {
                    int y1 = initHeight-gridHeight*(i+1)/rowSize;
                    int y2 = initHeight-gridHeight*i/rowSize;
                    int x1 = initWidth + gridWidth*j/columnSize;
                    int x2 = initWidth + gridWidth*(j+1)/columnSize;
                    cout << x1 << " " << x2 << " " << y1 << " " << y2 <<endl;
                    cout << _16[i][j] <<endl;
                    if(xButton >= x1 && xButton <= x2 && yButton >= y1 && yButton <= y2){
                        global=1;
                        gridI=i, gridJ=j;
                        if (_16[i][j] == -1)
                            global = 0;
                    }
                }
            }
        }
        else {
            global=0;
            int press=-1;
            for(int i = 0;i < 2 && press==-1;i++){
                glColor3dv(lineColor);
                glVertex2i(initButtonX + 50*i ,initButtonY);
                glVertex2i(initButtonX + 20 + 50*i ,initButtonY);
                glVertex2i(initButtonX +20 + 50*i ,initButtonY + 20);
                glVertex2i(initButtonX + 50*i ,initButtonY+20);
                int x11= initButtonX + 50*i , x22= initButtonX + 20 + 50*i;
                int y11 = initButtonY, y22= initButtonY+20;
                if(xButton >= x11 && xButton <= x22 && yButton >= y11 && yButton <= y22)
                    press=i;

            }
            int target = _16[gridI][gridJ];
            bool isPrime = target%2 && target%3 && target%5 && target %7;
            isPrime |= (target == 2 || target == 3 || target == 5 || target==7 );
            if(target ==1) isPrime=0;
            if(press != -1 && press != isPrime){
                if(numbers.size()){
                    int index = rand()%numbers.size();
                    _16[gridI][gridJ]=numbers[index];
                    numbers.erase(numbers.begin()+index);
                }
                else{
                    _16[gridI][gridJ]=-1;
                }

            }

        }

    }


    glutPostRedisplay();
}
void pre(){
    for(int i = 0;i < N_SIZE;i++) numbers[i]=i+1;
    for(int i = 0;i < rowSize;i++){
        for(int j = 0;j < columnSize;j++){
            int index = rand()%numbers.size();
            _16[i][j]=numbers[index];
            numbers.erase(numbers.begin()+index);
        }
    }
}
int main(int argc, char *argv[])
{
    srand(time(0));
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutCreateWindow("primeFactory");
    init();
    pre();
    glutDisplayFunc(Display);
    glutMouseFunc(mouse);
    glutMainLoop();

    return EXIT_SUCCESS;
}
