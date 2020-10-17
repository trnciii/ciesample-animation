#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLU
#include "GLFW/glfw3.h"
#include <math.h>
#include "box.hpp"

#define MAXFRAME 300.0

// 登場する関数
void myinit(GLFWwindow** window);
void reshape(GLFWwindow* window, int w, int h);
void display(int frame);

//--初期化—------------------------------------------------------------------
void myinit(GLFWwindow** window)
{
    glfwInit();
    
    int w = 600; // ウィンドウの幅
    int h = 600; // ウィンドウの高さ
    *window = glfwCreateWindow(w, h, "surface", NULL, NULL); // w*hの大きさで surface という名前のウィンドウをつくる
    glfwMakeContextCurrent(*window);
    glClearColor(0, 0, 0, 1); // 背景色の設定
    
    reshape(*window, w, h); // 視点の初期化をおこなう
    glEnable(GL_DEPTH_TEST);
}


//--再描画--------------------------------------------------------------------
void reshape(GLFWwindow* window, int w, int h)
{
    glViewport( 0, 0, (GLsizei)w, (GLsizei)h ); //ウィンドウ全体をビューポートにする
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
   
    gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
    gluLookAt(
        3.0, 4.0, 5.0,    //どこから見てるか
        0.0, 0.0, 0.0,    //どこを見てるか
        0.0, 1.0, 0.0    //どの向きが上向きか
    );
}

//--描画内容--------------------------------------------------------------------
void display(int frame)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    double angle = (double)360*frame/MAXFRAME; // frame から回転角を決める。MAXFRAME で一回転。
    glRotated(angle,0,0,1); // z軸回転させる
    makebox(1.0,1.0,1.0, GL_POLYGON);
}

//--メイン関数------------------------------------------------------------------
int main(void)
{
    //初期化処理 (ウィンドウサイズや表示位置、タイトル、背景色、...を決める)
    GLFWwindow* window; // ウィンドウの変数をつくる
    myinit(&window); // ウィンドウのポインタを渡して初期化
    

    //コールバック関数 (キーボードやマウスの動きを捕まえる)
    glfwSetWindowSizeCallback(window, reshape);
    
    
    // イベント処理ループ
    // 今回から時間(frame)を使ったアニメーションを行う。
    // frame は0から1ずつ増加し、MAXFRAMEまですすむと0に戻ることを繰り返す。  
    int frame = 0;
    do{
        frame++;
        if(MAXFRAME < frame)
            frame = 0;

        display(frame);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }while( !glfwWindowShouldClose(window) );//ウィンドウが表示されるかぎりループする

   glfwTerminate();

    return 0;
}

