
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <gtest/gtest.h>

#include "utils.hpp"

using chip_8::utils::TimePoint;

TEST(Utils, timediff) {
  TimePoint start = TimePoint::clock::now();
  std::cout << sizeof(start) << std::endl;
  std::cout << sizeof(&start) << std::endl;
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);             // 清空颜色缓冲池
  glColor3f(1.0f, 1.0f, 0.0f);              // 设置绘图颜色
  glRectf(100.0f, 100.0f, 200.0f, 200.0f);  // 绘制矩形
  glFlush();                                // 刷新缓冲
};

TEST(Monitor, CreatWindow) {
  int   argc   = 1;
  char* argv[] = {"test"};
  glutInit(&argc, argv);                           // 初始化glut库
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);     // 设置显示模式
  glutInitWindowSize(500, 500);                    // 设置窗口大小
  glutInitWindowPosition(200, 200);                // 设置窗口在屏幕上的位置
  glutCreateWindow("chip-8 emulator");             // 创建窗口并给出标题
  glutDisplayFunc(display);                        // 注册显示窗口时回调函数render
  glOrtho(0.0f, 300.0f, 0.0f, 300.0f, 1.0, -1.0);  // 设置窗口坐标系大小
  glClearColor(0.4f, 1.f, 0.8f, 1.0f);             // 设置背景色
  glutMainLoop();                                  // 处理操作系统等的消息，例如键盘、鼠标事件等
}