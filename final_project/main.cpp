#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL2_gfx.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>
#include<bits/stdc++.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <SDL2/SDL_mixer.h>
using namespace std ;
typedef std::pair<SDL_Texture*, std::string> ImagePair;
std::vector<ImagePair> images;
//****struct
struct line_1_2 {
    int line_1 [4];
    int line_2 [4];
};
struct balls_with_num {
    int ball[6][6] = {//تعریف رنگ توپ ها و دورنگ بودن یا نبودن - سطر اول همگی 0 مشکلی نداره - اولین هر کدام رنگ اصلی - آخری بمب دار
            {0, 0, 0, 0, 0, 0},
            {1, 9, 10, 13, 14, 17},//رنگ سبز
            {2, 6, 11, 13, 15, 19},//زرد
            {3, 6, 7, 8, 9, 18},//قرمز
            {4, 8, 12, 14, 15, 20},//بنفش
            {5, 7, 10, 11, 12, 21}//آبی
    };
};
//*********randomline
void list_toop_ha(int list [13][10],double & enteghali,int width,int mouse_x,int mouse_y,int & random_line_mode );
int cannon_random(int list[13][10],int mouse_x);
void first_second_line(line_1_2 &line);
int random_line(int list [3]);
//********
void play_music (vector<Mix_Music*>musics,int num , int volume);
void my_line (SDL_Renderer *renderer , int x_1 , int y_1 ,int l , double teta , int width , int r , int g , int b  );
//*******balls
void ball_green(SDL_Renderer * renderer,double x_center , double y_center, double width,std::vector<ImagePair> images);
void ball_red(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images);
void ball_purple(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images);
void ball_yellow(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images);
void ball_blue(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images);
void ball_red_yellow(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images);
void ball_red_blue(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images);
void ball_red_green(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images);
void ball_red_purple(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images);
void ball_blue_green(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images);
void ball_blue_yellow(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images);
void ball_blue_purple(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images);
void ball_green_yellow(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images);
void ball_green_purple(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images);
void ball_purple_yellow(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images);
void ball_black(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images);
void ball_lock_green(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images);
void ball_lock_red(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images);
void ball_lock_yellow(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images);
void ball_lock_purple(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images);
void ball_lock_blue(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images);
void ball_happy (SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images);
void main_balls(SDL_Renderer * renderer,int a ,double x_center , double y_center,double width,double height,std::vector<ImagePair> images);
//*******cannon
void line_cannon(SDL_Renderer *m_renderer,int x1, int y1,double x2,double y2,int dashLength, int gapLength,int width );
void shoot_ball(std::vector<ImagePair> images,int in_cannon,int list_toop[13][10],SDL_Renderer *m_renderer,int x1, int y1,int x2,int y2,int width);
//*************logic
void destroy_ball(SDL_Renderer * m_renderer,double enteghali,double x[10],double y[13],int list_toop[13][10],int i_old, int j_old , int i , int j , int coll, vector<int> & bonus ,  balls_with_num ballsWithNum,vector<int> & lock,int find,vector<Mix_Chunk *> song , double &time_effect,vector<ImagePair> images);
void back_lock(int list_toop [13][10],vector<int> &lock, balls_with_num ballsWithNum);
void d_ball(int list_toop[13][10],int i_old, int j_old , int i , int j , vector<int> & bonus,vector<int> & animation );
void g_ball(int list_toop[13][10],int i_0 , int j_0 ,int i_old , int j_old ,int i , int j, vector<int>bonus,vector<Mix_Chunk *>song  , vector<int> & animation);
void sort_list( vector<string> & mode , string name , int point);
void check_ball(int listtoop[13][10],int x_y_array[2] , double x_, double y_, double x[10],double y[13],int width);
int main( int argc, char * argv[] ) {
    SDL_Init(SDL_INIT_VIDEO);
    Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER;
    Uint32 WND_flags = SDL_WINDOW_SHOWN;// SDL_WINDOW_FULLSCREEN_DESKTOP ;//SDL_WINDOW_BORDERLESS ;// SDL_WINDOW_FULLSCREEN_DESKTOP ; ;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Texture *bkImg = NULL;
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("C:\\bouncing_ball\\font\\arial.ttf", 24);  // Replace "path_to_your_font.ttf" with the actual path to your TTF font file

    //Texture for loading image
    int img_w, img_h;
    SDL_Rect img_rect;
    SDL_DisplayMode DM;
    int W = DM.w;
    int H = DM.h;
    SDL_Init(SDL_flags);
    SDL_CreateWindowAndRenderer(900, 900, WND_flags, &m_window, &m_renderer);
    SDL_RaiseWindow(m_window);
    SDL_GetCurrentDisplayMode(0, &DM);
//این بخش از کد طول و عرض صفحه رو در دو متغیر ذخیره میکنه
    int w, h;
    SDL_GetRendererOutputSize(m_renderer, &w, &h);
    const int width = w, height = h;
    double adad_sabet_x = width * .2 - width * .04;
    double ghotr_dayere = .08 * width;
    double fasele_do_dayere = .08 * width;
    //***********************************************************************
// Load the images and store their textures
    for (int i = 1; i <= 28; ++i) {
        std::string imagePath = "C:/bouncing_ball/pic_balls/" + std::to_string(i) + ".png";
        SDL_Surface *imageSurface = IMG_Load(imagePath.c_str());
        SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, imageSurface);
        SDL_FreeSurface(imageSurface);
        images.push_back(std::make_pair(texture, imagePath));
    }

    //***********************************************************************
    double x[10]={adad_sabet_x+ghotr_dayere-.02*width-25,adad_sabet_x+2*ghotr_dayere-.02*width-20,adad_sabet_x+3*ghotr_dayere-.02*width-15,adad_sabet_x+4*ghotr_dayere-.02*width-10,adad_sabet_x+5*ghotr_dayere-.02*width-5,adad_sabet_x+6*ghotr_dayere-.02*width,adad_sabet_x+7*ghotr_dayere-.02*width+5,adad_sabet_x+8*ghotr_dayere-.02*width+10,adad_sabet_x+9*ghotr_dayere-.02*width+15,adad_sabet_x+10*ghotr_dayere-.02*width+20};
    double y[13]={(.04*width-2.5*fasele_do_dayere),(.04*width-1.5*fasele_do_dayere),(.04*width-.5*fasele_do_dayere),.04*width+.5*fasele_do_dayere,.04*width+1.5*fasele_do_dayere,.04*width+2.5*fasele_do_dayere,.04*width+3.5*fasele_do_dayere,.04*width+4.5*fasele_do_dayere,.04*width+5.5*fasele_do_dayere,.04*width+6.5*fasele_do_dayere,.04*width+7.5*fasele_do_dayere,.04*width+8.5*fasele_do_dayere,.04*width+9.5*fasele_do_dayere};
    int in_cannon = rand() % 5 + 1, out_cannon = rand() % 5 + 1;

    int counter_Setting = 0;
    int modes=3;
    int r=128,g=128,b=128 ;
    double time_effect=0;
    int x_1=280,y_1=350,x_2=530,y_2=350,x_3=780,y_3=350;
    int laser = 0 ;
    int power = 0 ;
    int check_win = 1;
    int p_m = 0 ;
    bool counter_line = 0 ;
    bool exit = true;
    bool pause = true;
    string name ;
    int x_ball=464;
    int y_ball=785 ;
    balls_with_num f;
    vector<int> bonus;
    vector<int> lock;
    vector<string>mode1 ;
    vector<string>mode2;
    vector<string>mode3 ;
    vector<int> animation_gball;
    vector<int> animation_d_ball;
//    ifstream fin("C:\\function\\pointdata\\1.txt", ios::in);
//    string a;
//    while (!fin.eof()){
//        getline(fin,a) ;
//        mode1.push_back(a);
//    }
//    fin.close();
//    ifstream in("C:\\function\\pointdata\\2.txt", ios::in);
//    while (!in.eof()){
//        getline(in,a) ;
//        mode2.push_back(a);
//    }
//    in.close();
//    ifstream f_in("C:\\function\\pointdata\\3.txt", ios::in);
//    while (!f_in.eof()){
//        getline(f_in,a) ;
//        mode3.push_back(a);
//    }
//    f_in.close();
//    sort_list(mode1,"amirali",150);
    //********************************
    // نقاط اصلی صفحه
    int list_toop[13][10];//لیست دو بعدی توپ ها
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 10; j++) {
            list_toop[i][j] = 0;
        }
    } // تعریف اولیه برای اینکه همه خانه ها 0 باشد
    line_1_2 line;
    first_second_line(line);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 10; j++) {
            if (i == 0 && j < 3) {
                list_toop[0][j] = line.line_1[0];
            } else if (i == 0 && j < 5) {
                list_toop[0][j] = line.line_1[1];
            } else if (i == 0 && j < 8) {
                list_toop[0][j] = line.line_1[2];
            } else if (i == 0 && j < 10) {
                list_toop[0][j] = line.line_1[3];
            }
            if (i == 1 && j < 3) {
                list_toop[1][j] = line.line_2[0];
            } else if (i == 1 && j < 5) {
                list_toop[1][j] = line.line_2[1];
            } else if (i == 1 && j < 8) {
                list_toop[1][j] = line.line_2[2];
            } else if (i == 1 && j < 10) {
                list_toop[1][j] = line.line_2[3];
            }
        }
    } // تعریف دو خط اول
    struct division_of_the_page {
        int x[3];//تقسیم بندی طول صفحه
        int y[12]; //تقسیم بندی عرض صفحه
    };
//*********************************
    int music_num = 6, volume = 32;
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 2048);

    vector<Mix_Music *> musics;
    for (int i = 1; i <= 8; ++i) {
        string m = "C:/bouncing_ball/music/" + to_string(i) + ".mp3";
        musics.push_back(Mix_LoadMUS(m.c_str()));
    }
    vector<Mix_Chunk * >song ;
    for (int i = 1; i <= 2; ++i) {
        string m = "C:/bouncing_ball/music/" + to_string(i) + ".wav";
        song.push_back(Mix_LoadWAV(m.c_str()));
    }


//******************************************************** وکتور آهنگ ها


    // Define a pair of SDL_Texture* and image path for each image
    typedef std::pair<SDL_Texture *, std::string> ImagePair;

    std::vector<ImagePair> tasavir;//اسم وکتور و تعریف
//*************************************** تعریف وکتور
    std::string imagePath = "C:/bouncing_ball/menu_pictures/1.jpg";//عکس پس زمینه اینجا آپلود میشه
    SDL_Surface *imageSurface = IMG_Load(imagePath.c_str());
    SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, imageSurface);
    SDL_FreeSurface(imageSurface);
    tasavir.push_back(std::make_pair(texture, imagePath));
    for (int i = 2; i <= 48; ++i) {
        std::string imagePath ="C:/bouncing_ball/menu_pictures/" + to_string(i) + ".png";//عکس های منو داخل وکتور هم آپلود میشه.
        SDL_Surface *imageSurface = IMG_Load(imagePath.c_str());
        SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, imageSurface);
        SDL_FreeSurface(imageSurface);
        tasavir.push_back(std::make_pair(texture, imagePath));
    }
    //*************************************************************************************
    struct back_g {
        int b[1][3]={{0,255,0}};
    };






    division_of_the_page p; //فراخوانی استراکت تقسیم بندی طولی و عرضی صفحه تحت عنوان p
    for (int i = 0; i < 12; i++) {
        p.y[i] = (height / 12 * i) - 50;//اینجا اعضای آرایه طول یا قد صفحه مقدار دهی میشن.
    }
    for (int j = 0; j < 3; j++) {
        p.x[j] = width / 3 * j;//اینجا اعضای آرایه عرض یا پهنای صفحه مقدار دهی میشن.
    }
    //***********
    SDL_Texture *image = tasavir[0].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه //تصویر پس زمینه
    SDL_Rect destinationRect = {0, 0, width, height}; // اینجا تصویر پس زمینه شروع بازی تعریف و قرار میگیره
    SDL_RenderCopy(m_renderer, image, NULL,&destinationRect); // تصویر در مختصات و ابعاد مشخص شده رندر میشه
    SDL_RenderPresent(m_renderer);
    SDL_Delay(1000);
    image = tasavir[44].first;
    destinationRect = {150, 300, 600, 200};
    SDL_RenderCopy(m_renderer, image, NULL,&destinationRect);
    SDL_RenderPresent(m_renderer);

    //**********
    bool isRunning = true;
    SDL_Event event;
    play_music(musics, music_num, volume);
    SDL_Event event_4;
    string userInput="" ;
    bool quit = false;
    while (!quit) {
        if (SDL_PollEvent(&event_4)) {
            if (event_4.type == SDL_QUIT) {
                quit = true;
            }
            else if (event_4.type == SDL_KEYDOWN) {
                // اضافه کردن کاراکتر‌ها به userInput
                userInput += event_4.key.keysym.sym;
            }
            if (event_4.type == SDL_KEYDOWN && event_4.key.keysym.sym == SDLK_RETURN) {
                quit = true;
            }
            if (event_4.type==SDL_MOUSEBUTTONDOWN) {
                int mx,my;
                SDL_GetMouseState(&mx, &my);
                if(mx<=550 && mx>=350 && my<=500 && my>=405){
                    quit = true;
                }

            }
        }
        SDL_Color textColor = {255, 255, 255};
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, userInput.c_str(), textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
        int textWidth= userInput.length()*10, textHeight=100;
        TTF_SizeText(font, userInput.c_str(), &textWidth, &textHeight);
        SDL_Rect textRect = {340, 325, textWidth, textHeight};
        SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect);
        SDL_RenderPresent(m_renderer);

    }

    while (isRunning) {
        bonus.clear();
        p_m=0;
        int mouseX=0, mouseY=0;
        if (SDL_PollEvent(&event)) {
            if (event.type==SDL_QUIT)
                isRunning = false;
            if (event.type==SDL_MOUSEBUTTONDOWN) {
                SDL_GetMouseState(&mouseX, &mouseY);
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                mouseX=34 ;// خروج از حلقه در صورت فشردن دکمه ESC
                mouseY=815 ;
            }


            SDL_Texture *image = tasavir[0].first;
            SDL_Rect destinationRect = {0, 0, width, height};
            SDL_RenderCopy(m_renderer, image, NULL,
                           &destinationRect);
            image = tasavir[1].first;
            destinationRect = {p.x[1], p.y[2], width / 3, height / 9};
            SDL_RenderCopy(m_renderer, image, NULL,
                           &destinationRect);
            image = tasavir[2].first;
            destinationRect = {p.x[1], p.y[4], width / 3, height / 9};
            SDL_RenderCopy(m_renderer, image, NULL,
                           &destinationRect);
            image = tasavir[3].first;
            destinationRect = {p.x[1], p.y[6], width / 3, height / 9};
            SDL_RenderCopy(m_renderer, image, NULL,
                           &destinationRect);
            image = tasavir[4].first;
            destinationRect = {p.x[1], p.y[8], width / 3, height / 9};
            SDL_RenderCopy(m_renderer, image, NULL,
                           &destinationRect);
            image = tasavir[5].first;
            destinationRect = {p.x[1], p.y[10], width / 3, height / 9};
            SDL_RenderCopy(m_renderer, image, NULL,
                           &destinationRect);
            image = tasavir[6].first;
            destinationRect = {p.x[0], p.y[11], 80, 80};
            SDL_RenderCopy(m_renderer, image, NULL,
                           &destinationRect);
            image = tasavir[25].first; // تصویر خروج یا اگزیت
            destinationRect = {820, 770, 45, 45};
            SDL_RenderCopy(m_renderer, image, NULL,
                           &destinationRect);

            SDL_RenderPresent(m_renderer);
            if ( exit && mouseX >= p.x[1] && mouseX <= p.x[1] + (width / 3) && mouseY >= p.y[2] &&mouseY <= p.y[2] + (height / 9)) {
                counter_line=0;
                if (modes==3 && exit) {
                    int random_line_mode=-1;
                    first_second_line(line);
                    int point=0;
                    double enteghali = .06;
                    int c = 0;//برای به هم نریختن هنگام سوییچ نوشته شده
                    while (exit) {
                        laser = point/20-(p_m);
                        string st = to_string(laser);
                        time_effect+=.001;
                        Mix_VolumeMusic(volume);
                        int mouseX1, mouseY1;
                        SDL_GetMouseState(&mouseX1, &mouseY1); // Get the current mouse position
                        int normalizedMouseX = static_cast<double>(mouseX1);
                        int normalizedMouseY = static_cast<double>(mouseY1);
                        SDL_SetRenderDrawColor(m_renderer, r, g ,b, 255);
                        SDL_RenderClear(m_renderer); // پاک کردن صفحه
                        boxRGBA(m_renderer, 0, 0, .2 * width - .05 * width, 900, 220, 160, 41, 255);
                        boxRGBA(m_renderer, 0, .05 * width + 10 * fasele_do_dayere, 900, 900, 220, 160, 41,255);
                        list_toop_ha(list_toop, enteghali, width, normalizedMouseX, normalizedMouseY,random_line_mode);
                        image = tasavir[46].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر خروج یا اگزیت
                        destinationRect = {80, 770, 100, 100}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                        SDL_RenderCopy(m_renderer, image, NULL,&destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                        //**************
                        SDL_Color textColor = {255, 255, 255};
                        SDL_Surface* textSurface = TTF_RenderText_Solid(font, st.c_str(), textColor);
                        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
                        int textWidth= st.length()*10, textHeight=100;
                        TTF_SizeText(font, st.c_str(), &textWidth, &textHeight);
                        SDL_Rect textRect = {80, 770, textWidth, textHeight};
                        SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect);
                        //**************
//                        string point_pointer=userInput+": "+ to_string(point);
//                        textSurface = TTF_RenderText_Solid(font, point_pointer.c_str(), textColor);
//                        textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
//                        TTF_SizeText(font, point_pointer.c_str(), &textWidth, &textHeight);
//                        textRect = {50, 50, textWidth, textHeight};
//                        SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect);
                        if(time_effect>0)
                            enteghali += .06;
                        for (int i = 0; i < 13; i++) {
                            for (int j = 0; j < 10; j++) {
                                main_balls(m_renderer, list_toop[i][j], x[j], y[i] + enteghali, width, height,
                                           images);
                            }

                        }
                        //**********************************

                        if (normalizedMouseY > 550 && normalizedMouseX < .2 * width - .05 * width) {
                            normalizedMouseY = 550, normalizedMouseX = .2 * width - .05 * width;
                        }
                        if (normalizedMouseY > 550)
                            normalizedMouseY = 550;
                        double angle = atan2(normalizedMouseX - 503, 740 - normalizedMouseY) * 180 /
                                       M_PI; // Calculate the angle based on mouse position
                        //cout<<angle<<endl;
                        SDL_Texture *image = images[21].first; // Get the image from the vector based on its index
                        SDL_Rect destinationRect = {443, 685, 110,200}; // Define the destination rectangle with dimensions 80x80
                        SDL_Point center = {55,100}; // Set the center of rotation to the center of the rectangle
                        SDL_RenderCopyEx(m_renderer, image, NULL, &destinationRect, angle, &center,SDL_FLIP_NONE); // Render the image at the specified coordinates and dimensions with rotation based on mouse position
                        angle = atan2(normalizedMouseX - (470 + .04 * width),745 + .04 * width - normalizedMouseY) * 180 / M_PI;
                        line_cannon(m_renderer, 498, 785, normalizedMouseX, normalizedMouseY, 20, 10, width);
                        //**************************************************خود cannon
                        SDL_Event event_1;
                        while (SDL_PollEvent(&event_1) != 0) {
                            time_effect += .001;
                            x_ball = 464;
                            y_ball = 785;
                            bool shoot = 1;
                            if (event_1.type == SDL_KEYDOWN && event_1.key.keysym.sym == SDLK_SPACE) {
                                int channel = Mix_PlayChannel(-1, song[0], 0);;
                                double v = 3;
                                double x_ = x_ball + .04 * width;
                                double y_ = y_ball + .04 * width;
                                double vy = -1 * abs(normalizedMouseY - y_ball);
                                double vx = normalizedMouseX - x_ball;
                                double zarib = v / sqrt(pow(vx, 2) + pow(vy, 2)) / 1.0;
                                vx = vx * zarib;
                                vy = vy * zarib;
                                while (y_ > -100 && shoot && y_ < 1000) {
                                    boxRGBA(m_renderer, .15 * width, 0, 900, .85 * width, r, g, b, 255);
                                    if (x_ > (900) || x_ < .2 * width)
                                        vx = -1 * vx;
                                    if (y_ < 0)
                                        vy = -1 * vy;
                                    x_ += vx;
                                    y_ += vy;
                                    image = images[in_cannon -
                                                   1].first; // Get the image from the vector based on its index
                                    destinationRect = {x_ - .04 * width, y_ - .04 * width, .08 * width,
                                                       .08 * width}; // Define the destination rectangle
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); // Render the image at the specified coordinates and dimensions

                                    for (int i = 12; i > 0; i--) {
                                        for (int j = 0; j < 10; j++) {
                                            if (list_toop[i][j] == 0)
                                                continue;
                                            if (sqrt(pow((x_ - x[j]), 2) + pow((y_ - (y[i] + enteghali)), 2)) <
                                                .065 * width) {
                                                int x_arr = j, y_arr = i;
                                                int x_y_arr[2] = {y_arr, x_arr};
                                                check_ball(list_toop, x_y_arr, x_, y_, x, y, width);
                                                x_arr = x_y_arr[1];
                                                y_arr = x_y_arr[0];
                                                list_toop[y_arr][x_arr] = 0;
                                                destroy_ball(m_renderer, enteghali, x, y, list_toop, y_arr,x_arr, y_arr, x_arr, in_cannon, bonus, f, lock, 0,song, time_effect, images);
                                                counter_line==1;
                                                back_lock(list_toop, lock, f);
                                                for (int p = 0; p < 13; p++) {
                                                    for (int c = 0; c < 10; c++) {
                                                        if (list_toop[p][c] == 0 && list_toop[p + 1][c] != 0) {
                                                            list_toop[p][c] = 37;
                                                            g_ball(list_toop, p, c, p, c, p, c, bonus, song,
                                                                   animation_gball);
                                                            if (animation_gball.size() > 0) {
                                                                for (int i: animation_gball) {
                                                                }
                                                                double enteghali_1 = 1;
                                                                for (int i = 0;
                                                                     i < (animation_gball.size() / 3); i++) {
                                                                    double y_center =
                                                                            y[animation_gball[i * 3]] +
                                                                            enteghali;
                                                                    while (y_center < 1000) {
                                                                        y_center += enteghali_1;
                                                                        SDL_SetRenderDrawColor(m_renderer, r, g,
                                                                                               b,
                                                                                               255);
                                                                        SDL_RenderClear(m_renderer);
                                                                        boxRGBA(m_renderer, 0, 0,
                                                                                .2 * width - .05 * width, 900,
                                                                                220, 160, 41, 255);
                                                                        boxRGBA(m_renderer, 0, .05 * width +
                                                                                               10 *
                                                                                               fasele_do_dayere,
                                                                                900, 900, 220, 160, 41, 255);
                                                                        for (int i = 0; i < 13; i++) {
                                                                            for (int j = 0; j < 10; j++) {
                                                                                main_balls(m_renderer,
                                                                                           list_toop[i][j],
                                                                                           x[j],
                                                                                           y[i] + enteghali,
                                                                                           width, height,
                                                                                           images);
                                                                            }
                                                                        }
                                                                        main_balls(m_renderer,
                                                                                   animation_gball[i * 3 + 2],
                                                                                   x[animation_gball[3 * i +
                                                                                                     1]],
                                                                                   y_center, width, width,
                                                                                   images);
                                                                        SDL_Texture *image = images[21].first; // Get the image from the vector based on its index
                                                                        SDL_Rect destinationRect = {443, 685,
                                                                                                    110,
                                                                                                    200}; // Define the destination rectangle with dimensions 80x80
                                                                        SDL_Point center = {55,
                                                                                            100}; // Set the center of rotation to the center of the rectangle
                                                                        SDL_RenderCopyEx(m_renderer, image,
                                                                                         NULL, &destinationRect,
                                                                                         angle, &center,
                                                                                         SDL_FLIP_NONE); // Render the image at the specified coordinates and dimensions with rotation based on mouse position
                                                                        angle = atan2(normalizedMouseX -
                                                                                      (470 + .04 * width),
                                                                                      745 + .04 * width -
                                                                                      normalizedMouseY) * 180 /
                                                                                M_PI;
                                                                        line_cannon(m_renderer, 498, 785,
                                                                                    normalizedMouseX,
                                                                                    normalizedMouseY, 20, 10,
                                                                                    width);

                                                                        SDL_RenderPresent(m_renderer);
                                                                    }

                                                                }
                                                                animation_gball.clear();

                                                            }
                                                            for (int o = 0; o < 13; o++) {
                                                                for (int z = 0; z < 10; z++) {
                                                                    if (list_toop[o][z] == 43 ||
                                                                        list_toop[o][z] == 37) {
                                                                        list_toop[o][z] = 0;
                                                                    }
                                                                }
                                                            }

                                                        }
                                                    }
                                                }

                                                shoot = 0;
                                                break;
                                            }
                                        }
                                    }
                                    //***********************************************
                                    boxRGBA(m_renderer, 0, 0, .2 * width - .05 * width, 900, 220, 160, 41, 255);
                                    boxRGBA(m_renderer, 0, .05 * width + 10 * fasele_do_dayere, 900, 900, 220,
                                            160, 41, 255);
                                    list_toop_ha(list_toop, enteghali, width, normalizedMouseX,
                                                 normalizedMouseY,random_line_mode);
                                    time_effect += .001;
                                    if (time_effect > 0)
                                        enteghali += 0.06;
                                    for (int i = 0; i < 13; i++) {
                                        for (int j = 0; j < 10; j++) {
                                            main_balls(m_renderer, list_toop[i][j], x[j], y[i] + enteghali,
                                                       width, height, images);
                                        }

                                    }
                                    double angle = atan2(normalizedMouseX - 503, 740 - normalizedMouseY) * 180 /
                                                   M_PI; // Calculate the angle based on mouse position
                                    //cout<<angle<<endl;
                                    image = images[21].first; // Get the image from the vector based on its index
                                    destinationRect = {443, 685, 110,
                                                       200}; // Define the destination rectangle with dimensions 80x80
                                    SDL_Point center = {55,
                                                        100}; // Set the center of rotation to the center of the rectangle
                                    SDL_RenderCopyEx(m_renderer, image, NULL, &destinationRect, angle, &center,
                                                     SDL_FLIP_NONE); // Render the image at the specified coordinates and dimensions with rotation based on mouse position
                                    angle = atan2(normalizedMouseX - (470 + .04 * width),
                                                  745 + .04 * width - normalizedMouseY) * 180 / M_PI;
                                    line_cannon(m_renderer, 498, 785, normalizedMouseX, normalizedMouseY, 20,
                                                10, width);
                                    image = tasavir[6].first; // Get the image from the vector based on its index //تصویر تنظیمات بازی
                                    destinationRect = {p.x[0], p.y[11], 80,
                                                       80}; // Define the destination rectangle
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); // Render the image at the specified coordinates and dimensions
                                    image = tasavir[46].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر خروج یا اگزیت
                                    destinationRect = {80, 770, 100,
                                                       100}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                    image = tasavir[25].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر خروج یا اگزیت
                                    destinationRect = {820, 770, 45,
                                                       45}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه

                                    SDL_RenderPresent(m_renderer);

                                }
                                in_cannon = out_cannon;
                                out_cannon = cannon_random(list_toop, normalizedMouseX);
//                                cout<<out_cannon;
                            }
                            if((event_1.key.keysym.sym == SDLK_LSHIFT || event_1.key.keysym.sym == SDLK_RSHIFT )&& laser>0){
                                power=1 ;
                            }
                            if (event_1.type == SDL_MOUSEBUTTONDOWN) {
                                SDL_GetMouseState(&mouseX, &mouseY);
                                if ((mouseX - (200 + .04 * width)) * (mouseX - (200 + .04 * width)) +(mouseY - (800 + .04 * width)) * (mouseY - (800 + .04 * width)) <=(.04 * width) * (.04 * width))
                                    swap(in_cannon, out_cannon);
                                if(power == 1) {
                                    point -= 50;
                                    p_m += 1;

                                    //laser***************
                                    int stoon;
                                    if (mouseX < x[0])
                                        stoon = 0;
                                    if (mouseX > x[0] && mouseX < x[1])
                                        stoon = 1;
                                    if (mouseX > x[1] && mouseX < x[2])
                                        stoon = 2;
                                    if (mouseX > x[2] && mouseX < x[3])
                                        stoon = 3;
                                    if (mouseX > x[3] && mouseX < x[4])
                                        stoon = 4;
                                    if (mouseX > x[4] && mouseX < x[5])
                                        stoon = 5;
                                    if (mouseX > x[5] && mouseX < x[6])
                                        stoon = 6;
                                    if (mouseX > x[6] && mouseX < x[7])
                                        stoon = 7;
                                    if (mouseX > x[7] && mouseX < x[8])
                                        stoon = 8;
                                    if (mouseX > x[8] && mouseX < x[9])
                                        stoon = 9;
                                    if (mouseX > x[9])
                                        stoon = 9;
                                    image = tasavir[47].first; // Get the image from the vector based on its index //تصویر تنظیمات بازی
                                    destinationRect = {mouseX, mouseY, 40, 150}; // Define the destination rectangle
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); // Render the image at the specified coordinates and dimensions
                                    boxRGBA(m_renderer,mouseX,mouseY,mouseX+40,0,250,163,22,255);
                                    SDL_RenderPresent(m_renderer);
                                    SDL_Delay(500);
                                    for (int i = 1; i < 13; i++) {
                                        list_toop[i][stoon] = 0;
                                    }
                                    power = 0;

                                }
                                //********************** laser
                            }
                            if (event_1.type == SDL_QUIT) {
                                exit = false; // خروج از حلقه در صورت بستن پنجره
                            }
                            if (event_1.type == SDL_KEYDOWN && event_1.key.keysym.sym == SDLK_ESCAPE) {
                                mouseX = 34;// خروج از حلقه در صورت فشردن دکمه ESC
                                mouseY = 815;
                            }
                            if (event_1.type == SDL_MOUSEWHEEL) {
                                if (event_1.wheel.y > 0 && volume < 128) {
                                    volume += 4; // Scroll right

                                } else if (event_1.wheel.y < 0 && volume > 0) {
                                    volume -= 4; // Scroll left
                                }
//                                            cout << volume << endl;

                            }
//                                    ofstream fout("C:\\function\\data.txt",ios::app);
//                                    for(int o = 0 ; o<13 ; o++) {
//                                        for(int z = 0 ; z<10 ; z++) {
//                                            fout<<list_toop[o][z]<<" ";
//                                        }
//                                        fout<<endl ;
//                                    }
//                                    fout.close();
                        }
                        image = tasavir[6].first; // Get the image from the vector based on its index //تصویر تنظیمات بازی
                        destinationRect = {p.x[0], p.y[11], 80, 80}; // Define the destination rectangle
                        SDL_RenderCopy(m_renderer, image, NULL,
                                       &destinationRect); // Render the image at the specified coordinates and dimensions
                        image = tasavir[25].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر خروج یا اگزیت
                        destinationRect = {820, 770, 45, 45}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                        SDL_RenderCopy(m_renderer, image, NULL,
                                       &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                        image = images[in_cannon -1].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر مود های بازی
                        destinationRect = {x_ball, y_ball, .08 * width,
                                           .08 * width}; // مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                        center = {34, 0}; // Set the center of rotation to the center of the rectangle
                        SDL_RenderCopyEx(m_renderer, image, NULL, &destinationRect, angle, &center,
                                         SDL_FLIP_NONE); // Render the image at the specified coordinates and dimensions with rotation based on mouse position
                        image = images[out_cannon -1].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر مود های بازی
                        destinationRect = {200, 800, .08 * width,
                                           .08 * width}; // مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                        SDL_RenderCopy(m_renderer, image, NULL,
                                       &destinationRect); // تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                        aalineRGBA(m_renderer, .2 * width - .05 * width, .05 * width + 10 * fasele_do_dayere,
                                   width, .05 * width + 10 * fasele_do_dayere, 255, 255, 255, 255);
                        aalineRGBA(m_renderer, .2 * width - .05 * width, 0, .2 * width - .05 * width,
                                   .05 * width + 10 * fasele_do_dayere, 255, 255, 255, 255);
                        if (pause &&
                            pow((mouseX - (p.x[0] + 80 / 2)), 2) + pow((mouseY - (p.y[11] + 80 / 2)), 2) <=
                            1600) {
                            if (counter_Setting == 0) {
                                SDL_RenderClear(m_renderer);
                                image = tasavir[24].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه //تصویر پس زمینه
                                destinationRect = {0, 0, 900,
                                                   900}; // اینجا تصویر پس زمینه شروع بازی تعریف و قرار میگیره
                                SDL_RenderCopy(m_renderer, image, NULL,
                                               &destinationRect); // تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                SDL_RenderPresent(m_renderer);
                                SDL_Delay(500);
                                counter_Setting = 1;
                            }

                            //SDL_RenderClear(m_renderer); // پاک کردن صفحه
                            //گر اگزیت کلیک شد اگزیت به فالس تبدیل میشه و کانتر ستینگ برابر با صفر شود در انتها
                            //SDL_Delay(2000);
                            image = tasavir[18].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه //تصویر ااولین اهنگ
                            destinationRect = {p.x[0], p.y[2], 300,
                                               300}; // اینجا تصویر پس زمینه شروع بازی تعریف و قرار میگیره
                            SDL_RenderCopy(m_renderer, image, NULL,
                                           &destinationRect); // تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                            image = tasavir[19].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر دملین اهنگ
                            destinationRect = {p.x[1], p.y[2], 300,
                                               300}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                            SDL_RenderCopy(m_renderer, image, NULL,
                                           &destinationRect); // تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                            image = tasavir[20].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر سومین اهنگ
                            destinationRect = {p.x[2], p.y[2], 300,
                                               300}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                            SDL_RenderCopy(m_renderer, image, NULL,
                                           &destinationRect); // تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                            image = tasavir[21].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر چهارمین اهنگ
                            destinationRect = {p.x[0], p.y[6], 300,
                                               300}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                            SDL_RenderCopy(m_renderer, image, NULL,
                                           &destinationRect); // تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                            image = tasavir[22].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر پنجمین اهنگ
                            destinationRect = {p.x[1], p.y[6], 300,
                                               300}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                            SDL_RenderCopy(m_renderer, image, NULL,
                                           &destinationRect); // تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                            image = tasavir[23].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تتصویر ششمین اهنگ
                            destinationRect = {p.x[2], p.y[6], 300,
                                               300}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                            SDL_RenderCopy(m_renderer, image, NULL,
                                           &destinationRect); // تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                            image = tasavir[7].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر تنظیم حجم صدا
                            destinationRect = {375, 750, 206, 50}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                            SDL_RenderCopy(m_renderer, image, NULL,
                                           &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                            image = tasavir[25].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر خروج یا اگزیت
                            destinationRect = {820, 770, 45, 45}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                            SDL_RenderCopy(m_renderer, image, NULL,
                                           &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                            SDL_RenderPresent(m_renderer);
                            SDL_Event Event;
                            while (pause) {
                                Mix_VolumeMusic(volume);
                                if (SDL_PollEvent(&Event)) {
                                    if (Event.type == SDL_MOUSEBUTTONDOWN) {
                                        int mouse_X2, mouse_Y2;
                                        SDL_GetMouseState(&mouse_X2, &mouse_Y2);
                                        if (mouse_X2 >= p.x[0] && mouse_X2 <= p.x[0] + 300 &&
                                            mouse_Y2 >= p.y[2] && mouse_Y2 <= p.y[2] + 300) {
                                            music_num = 1;
                                            Mix_HaltMusic();
                                            play_music(musics, music_num, volume);
                                        }
                                        if (mouse_X2 >= p.x[1] && mouse_X2 <= p.x[1] + 300 &&
                                            mouse_Y2 >= p.y[2] && mouse_Y2 <= p.y[2] + 300) {
                                            music_num = 2;
                                            Mix_HaltMusic();
                                            play_music(musics, music_num, volume);

                                        }
                                        if (mouse_X2 >= p.x[2] && mouse_X2 <= p.x[2] + 300 &&
                                            mouse_Y2 >= p.y[2] && mouse_Y2 <= p.y[2] + 300) {
                                            music_num = 3;
                                            Mix_HaltMusic();
                                            play_music(musics, music_num, volume);

                                        }
                                        if (mouse_X2 >= p.x[0] && mouse_X2 <= p.x[0] + 300 &&
                                            mouse_Y2 >= p.y[6] && mouse_Y2 <= p.y[6] + 300) {
                                            music_num = 4;
                                            Mix_HaltMusic();
                                            play_music(musics, music_num, volume);

                                        }
                                        if (mouse_X2 >= p.x[1] && mouse_X2 <= p.x[1] + 300 &&
                                            mouse_Y2 >= p.y[6] && mouse_Y2 <= p.y[6] + 300) {
                                            music_num = 5;
                                            Mix_HaltMusic();
                                            play_music(musics, music_num, volume);

                                        }
                                        if (mouse_X2 >= p.x[2] && mouse_X2 <= p.x[2] + 300 &&
                                            mouse_Y2 >= p.y[6] && mouse_Y2 <= p.y[6] + 300) {
                                            music_num = 6;
                                            Mix_HaltMusic();
                                            play_music(musics, music_num, volume);
                                        }
                                        //گر اگزیت کلیک شد اگزیت به فالس تبدیل میشه و کانتر ستینگ برابر با صفر شود در انتها
                                        if (mouse_X2 >= 820 && mouse_X2 <= 820 + 45 && mouse_Y2 >= 770 &&
                                            mouse_Y2 <= 770 + 45) {
                                            pause = false;
                                            counter_Setting = 0;
                                        }
                                    }
                                    if (Event.type == SDL_KEYDOWN && Event.key.keysym.sym == SDLK_ESCAPE) {
                                        pause = false;
                                        counter_Setting = 0;
                                    }
                                    if (Event.type == SDL_MOUSEWHEEL) {
                                        if (Event.wheel.y > 0 && volume < 128) {
                                            volume += 4; // Scroll right

                                        } else if (Event.wheel.y < 0 && volume > 0) {
                                            volume -= 4; // Scroll left
                                        }
//                                        cout << volume << endl;
                                        Mix_VolumeMusic(volume);

                                    }
                                }

                                if (volume < 12) {
                                    boxRGBA(m_renderer, 377, 757, 397, 787, 255, 255, 255, 255);
                                }
                                if (volume < 24) {
                                    boxRGBA(m_renderer, 397, 757, 397, 787, 255, 255, 255, 255);
                                }
                                if (volume < 36) {
                                    boxRGBA(m_renderer, 417, 757, 397, 787, 255, 255, 255, 255);
                                }
                                if (volume < 48) {
                                    boxRGBA(m_renderer, 437, 757, 397, 787, 255, 255, 255, 255);
                                }
                                if (volume < 60) {
                                    boxRGBA(m_renderer, 457, 757, 397, 787, 255, 255, 255, 255);
                                }
                                if (volume < 74) {
                                    boxRGBA(m_renderer, 477, 757, 397, 787, 255, 255, 255, 255);
                                }
                                if (volume < 88) {
                                    boxRGBA(m_renderer, 497, 757, 397, 787, 255, 255, 255, 255);
                                }
                                if (volume < 102) {
                                    boxRGBA(m_renderer, 517, 757, 397, 787, 255, 255, 255, 255);
                                }
                                if (volume < 116) {
                                    boxRGBA(m_renderer, 537, 757, 397, 787, 255, 255, 255, 255);
                                }
                                if (volume < 129) {
                                    boxRGBA(m_renderer, 557, 757, 397, 787, 255, 255, 255, 255);
                                    boxRGBA(m_renderer, 577, 757, 397, 787, 255, 255, 255, 255);
                                }
                                if (volume > 12) {
                                    image = tasavir[8].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر اولین حجم صدا
                                    destinationRect = {377, 757, 20,
                                                       30}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                }
                                if (volume > 24) {
                                    image = tasavir[10].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر اولین حجم صدا
                                    destinationRect = {397, 757, 20,
                                                       30}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                }

                                if (volume > 36) {
                                    image = tasavir[11].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر اولین حجم صدا
                                    destinationRect = {417, 757, 20,
                                                       30}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                }

                                if (volume > 48) {
                                    image = tasavir[12].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر اولین حجم صدا
                                    destinationRect = {437, 757, 20,
                                                       30}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                }

                                if (volume > 60) {
                                    image = tasavir[12].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر اولین حجم صدا
                                    destinationRect = {457, 757, 20,
                                                       30}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                }

                                if (volume > 74) {
                                    image = tasavir[13].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر اولین حجم صدا
                                    destinationRect = {477, 757, 20,
                                                       30}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                }

                                if (volume > 88) {
                                    image = tasavir[14].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر اولین حجم صدا
                                    destinationRect = {497, 757, 20,
                                                       30}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                }

                                if (volume > 102) {
                                    image = tasavir[15].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر اولین حجم صدا
                                    destinationRect = {517, 757, 20,
                                                       30}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                }

                                if (volume > 116) {
                                    image = tasavir[16].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر اولین حجم صدا
                                    destinationRect = {537, 757, 20,
                                                       30}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                }

                                if (volume == 124 || volume == 128) {
                                    image = tasavir[17].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر اولین حجم صدا
                                    destinationRect = {557, 757, 20,
                                                       30}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                }

                                SDL_RenderPresent(m_renderer);
                                //تصویر تنظیمات
                            }
                            mouseX = 0;
                            mouseY = 0;
                        }
                        pause = true;
                        if (exit && mouseX >= 820 && mouseX <= 820 + 45 && mouseY >= 770 &&
                            mouseY <= 770 + 45) {
                            for (int i = 2; i < 13; i++) {
                                for (int j = 0; j < 10; j++) {
                                    list_toop[i][j] = 0;
                                }
                            }
                            mouseX = 0;
                            mouseY = 0;
                            exit = 0;
                        }
                        point=bonus.size();//محاسبه امتیاز
                        //***************************************
                        //خط های دور صفحه
                        for (int j = 0; j < 10; j++) {//خطی که برای سوختن استفاده شد .
                            if (list_toop[12][j] != 0) {
                                for (int i = 2; i < 13; i++) {
                                    for (int j = 0; j < 10; j++) {
                                        list_toop[i][j] = 0;
                                    }
                                }
//                                ofstream fout("C:\\function\\pointdata\\3.txt", ios::out);
//                                sort_list(mode3, userInput, point);
//                                for (int i = 0; i < mode3.size(); i++) {
//                                    fout << mode3[i] << endl;
//                                }
//                                fout.close();

                                SDL_Event event3;
                                int m_x, m_y;
                                while (exit) {
                                    image = tasavir[36].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر خروج یا اگزیت
                                    destinationRect = {0, 0, 900,900}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                    image = tasavir[35].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر خروج یا اگزیت
                                    destinationRect = {280, 400, 250,60}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                    image = tasavir[25].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر خروج یا اگزیت
                                    destinationRect = {820, 770, 45,
                                                       45}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                    if (SDL_PollEvent(&event3)) {
                                        if (event3.type == SDL_MOUSEBUTTONDOWN) {
                                            SDL_GetMouseState(&m_x, &m_y);
                                            if (m_x >= 820 && m_x <= 820 + 45 && m_y >= 770 &&m_y <= 770 + 45) {
                                                exit = false;
                                            }
                                        }
                                    }
                                    string pouan = to_string(point);
                                    SDL_Color textColor = {0, 0, 0};
                                    SDL_Surface* textSurface = TTF_RenderText_Solid(font, pouan.c_str(), textColor);
                                    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
                                    int textWidth= pouan.length()*10, textHeight=180;
                                    TTF_SizeText(font, pouan.c_str(), &textWidth, &textHeight);
                                    SDL_Rect textRect = {510, 415, textWidth, textHeight};
                                    SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect);
                                    SDL_RenderPresent(m_renderer);
                                }
                                break ;
                            }
                        }
                        SDL_RenderPresent(m_renderer);

                    }

                }
                if(modes==2 && exit){
                    first_second_line(line);
                    int random_line_for_mode = 4;
                    int point=0;
                    double enteghali = .06;
                    int c = 0;//برای به هم نریختن هنگام سوییچ نوشته شده
                    while (exit) {
//                                cout<<random_line_for_mode<<endl;
                        laser = point/20-(p_m);
                        string st = to_string(laser);
                        time_effect+=.001;
                        Mix_VolumeMusic(volume);
                        int mouseX1, mouseY1;
                        SDL_GetMouseState(&mouseX1, &mouseY1); // Get the current mouse position
                        int normalizedMouseX = static_cast<double>(mouseX1);
                        int normalizedMouseY = static_cast<double>(mouseY1);
                        SDL_SetRenderDrawColor(m_renderer, r, g ,b, 255); // تنظیم رنگ مشکی بکگراند
                        SDL_RenderClear(m_renderer); // پاک کردن صفحه
                        boxRGBA(m_renderer, 0, 0, .2 * width - .05 * width, 900, 220, 160, 41, 255);
                        boxRGBA(m_renderer, 0, .05 * width + 10 * fasele_do_dayere, 900, 900, 220, 160, 41,255);
                        list_toop_ha(list_toop, enteghali, width, normalizedMouseX, normalizedMouseY,random_line_for_mode);
                        int y_line = 0;
                        if(random_line_for_mode==0){
                            for(int y = 0 ; y<13 ; y++) {
                                for(int k = 0 ; k<10 ; k++){
                                    if(list_toop[y][k]==80)
                                        y_line=y;

                                }
                            }
                        }
                        boxRGBA(m_renderer,.15*width,y[y_line+1]+enteghali-5,900,y[y_line+1]+enteghali-20,255,255,255,255);
                        image = tasavir[46].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر خروج یا اگزیت
                        destinationRect = {80, 770, 100, 100}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                        SDL_RenderCopy(m_renderer, image, NULL,&destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                        SDL_Color textColor = {255, 255, 255};
                        SDL_Surface* textSurface = TTF_RenderText_Solid(font, st.c_str(), textColor);
                        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
                        int textWidth= st.length()*10, textHeight=100;
                        TTF_SizeText(font, st.c_str(), &textWidth, &textHeight);
                        SDL_Rect textRect = {80, 770, textWidth, textHeight};
                        SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect);
                        //*********
//                        string point_pointer=userInput+": "+ to_string(point);
//                        textSurface = TTF_RenderText_Solid(font, point_pointer.c_str(), textColor);
//                        textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
//                        TTF_SizeText(font, point_pointer.c_str(), &textWidth, &textHeight);
//                        textRect = {50, 50, textWidth, textHeight};
//                        SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect);

                        if(time_effect>0)
                            enteghali += .06;
                        for (int i = 0; i < 13; i++) {
                            for (int j = 0; j < 10; j++) {
                                main_balls(m_renderer, list_toop[i][j], x[j], y[i] + enteghali, width, height,images);
                            }

                        }
                        //**********************************

                        if (normalizedMouseY > 550 && normalizedMouseX < .2 * width - .05 * width) {
                            normalizedMouseY = 550, normalizedMouseX = .2 * width - .05 * width;
                        }
                        if (normalizedMouseY > 550)
                            normalizedMouseY = 550;
                        double angle = atan2(normalizedMouseX - 503, 740 - normalizedMouseY) * 180 /
                                       M_PI; // Calculate the angle based on mouse position
                        //cout<<angle<<endl;
                        SDL_Texture *image = images[21].first; // Get the image from the vector based on its index
                        SDL_Rect destinationRect = {443, 685, 110,200}; // Define the destination rectangle with dimensions 80x80
                        SDL_Point center = {55,100}; // Set the center of rotation to the center of the rectangle
                        SDL_RenderCopyEx(m_renderer, image, NULL, &destinationRect, angle, &center,SDL_FLIP_NONE); // Render the image at the specified coordinates and dimensions with rotation based on mouse position
                        angle = atan2(normalizedMouseX - (470 + .04 * width),745 + .04 * width - normalizedMouseY) * 180 / M_PI;
                        line_cannon(m_renderer, 498, 785, normalizedMouseX, normalizedMouseY, 20, 10, width);
                        //**************************************************خود cannon
                        SDL_Event event_1;
                        while (SDL_PollEvent(&event_1) != 0) {
                            time_effect += .001;
                            x_ball = 464;
                            y_ball = 785;
                            bool shoot = 1;
                            if (event_1.type == SDL_KEYDOWN && event_1.key.keysym.sym == SDLK_SPACE) {
                                int channel = Mix_PlayChannel(-1, song[0], 0);;
                                double v = 3;
                                double x_ = x_ball + .04 * width;
                                double y_ = y_ball + .04 * width;
                                double vy = -1 * abs(normalizedMouseY - y_ball);
                                double vx = normalizedMouseX - x_ball;
                                double zarib = v / sqrt(pow(vx, 2) + pow(vy, 2)) / 1.0;
                                vx = vx * zarib;
                                vy = vy * zarib;
                                while (y_ > -100 && shoot && y_ < 1000) {
                                    boxRGBA(m_renderer, .15 * width, 0, 900, .85 * width, r, g, b, 255);
                                    if (x_ > (900) || x_ < .2 * width)
                                        vx = -1 * vx;
                                    if (y_ < 0)
                                        vy = -1 * vy;
                                    x_ += vx;
                                    y_ += vy;
                                    image = images[in_cannon -
                                                   1].first; // Get the image from the vector based on its index
                                    destinationRect = {x_ - .04 * width, y_ - .04 * width, .08 * width,
                                                       .08 * width}; // Define the destination rectangle
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); // Render the image at the specified coordinates and dimensions

                                    for (int i = 12; i > 0; i--) {
                                        for (int j = 0; j < 10; j++) {
                                            if (list_toop[i][j] == 0)
                                                continue;
                                            if (sqrt(pow((x_ - x[j]), 2) + pow((y_ - (y[i] + enteghali)), 2)) <
                                                .065 * width) {
//                                                            cout<<x_<<" | "<<y_<<endl;
                                                int x_arr = j, y_arr = i;
                                                int x_y_arr[2] = {y_arr, x_arr};
                                                check_ball(list_toop, x_y_arr, x_, y_, x, y, width);
                                                x_arr = x_y_arr[1];
                                                y_arr = x_y_arr[0];
                                                list_toop[y_arr][x_arr] = 0;
                                                destroy_ball(m_renderer, enteghali, x, y, list_toop, y_arr,
                                                             x_arr, y_arr, x_arr, in_cannon, bonus, f, lock, 0,
                                                             song, time_effect, images);
                                                back_lock(list_toop, lock, f);
                                                for (int p = 0; p < 13; p++) {
                                                    for (int c = 0; c < 10; c++) {
                                                        if (list_toop[p][c] == 0 && list_toop[p + 1][c] != 0) {
                                                            list_toop[p][c] = 37;
                                                            g_ball(list_toop, p, c, p, c, p, c, bonus, song,
                                                                   animation_gball);
                                                            if (animation_gball.size() > 0) {
//                                                                        cout<<"****";
                                                                for (int i: animation_gball) {
//                                                                            cout<<i<<endl;
                                                                }
                                                                double enteghali_1 = 1;
                                                                for (int i = 0;
                                                                     i < (animation_gball.size() / 3); i++) {
                                                                    double y_center =
                                                                            y[animation_gball[i * 3]] +
                                                                            enteghali;
                                                                    while (y_center < 1000) {
                                                                        y_center += enteghali_1;
                                                                        SDL_SetRenderDrawColor(m_renderer, r, g,
                                                                                               b,
                                                                                               255); // تنظیم رنگ مشکی بکگراند
                                                                        SDL_RenderClear(m_renderer);
                                                                        boxRGBA(m_renderer, 0, 0,
                                                                                .2 * width - .05 * width, 900,
                                                                                220, 160, 41, 255);
                                                                        boxRGBA(m_renderer, 0, .05 * width +
                                                                                               10 *
                                                                                               fasele_do_dayere,
                                                                                900, 900, 220, 160, 41, 255);
                                                                        for (int i = 0; i < 13; i++) {
                                                                            for (int j = 0; j < 10; j++) {
                                                                                main_balls(m_renderer,
                                                                                           list_toop[i][j],
                                                                                           x[j],
                                                                                           y[i] + enteghali,
                                                                                           width, height,
                                                                                           images);
                                                                            }
                                                                        }
                                                                        main_balls(m_renderer,
                                                                                   animation_gball[i * 3 + 2],
                                                                                   x[animation_gball[3 * i +
                                                                                                     1]],
                                                                                   y_center, width, width,
                                                                                   images);
                                                                        SDL_Texture *image = images[21].first; // Get the image from the vector based on its index
                                                                        SDL_Rect destinationRect = {443, 685,
                                                                                                    110,
                                                                                                    200}; // Define the destination rectangle with dimensions 80x80
                                                                        SDL_Point center = {55,
                                                                                            100}; // Set the center of rotation to the center of the rectangle
                                                                        SDL_RenderCopyEx(m_renderer, image,
                                                                                         NULL, &destinationRect,
                                                                                         angle, &center,
                                                                                         SDL_FLIP_NONE); // Render the image at the specified coordinates and dimensions with rotation based on mouse position
                                                                        angle = atan2(normalizedMouseX -
                                                                                      (470 + .04 * width),
                                                                                      745 + .04 * width -
                                                                                      normalizedMouseY) * 180 /
                                                                                M_PI;
                                                                        line_cannon(m_renderer, 498, 785,
                                                                                    normalizedMouseX,
                                                                                    normalizedMouseY, 20, 10,
                                                                                    width);

                                                                        SDL_RenderPresent(m_renderer);
                                                                    }

                                                                }
                                                                animation_gball.clear();

                                                            }
                                                            for (int o = 0; o < 13; o++) {
                                                                for (int z = 0; z < 10; z++) {
                                                                    if (list_toop[o][z] == 43 ||
                                                                        list_toop[o][z] == 37) {
                                                                        list_toop[o][z] = 0;
                                                                    }
                                                                }
                                                            }

                                                        }
                                                    }
                                                }

                                                shoot = 0;
                                                break;
                                            }
                                        }
                                    }
                                    //***********************************************
                                    boxRGBA(m_renderer, 0, 0, .2 * width - .05 * width, 900, 220, 160, 41, 255);
                                    boxRGBA(m_renderer, 0, .05 * width + 10 * fasele_do_dayere, 900, 900, 220,
                                            160, 41, 255);
                                    list_toop_ha(list_toop, enteghali, width, normalizedMouseX,
                                                 normalizedMouseY,random_line_for_mode);
                                    time_effect += .001;
                                    if (time_effect > 0)
                                        enteghali += 0.06;
                                    for (int i = 0; i < 13; i++) {
                                        for (int j = 0; j < 10; j++) {
                                            main_balls(m_renderer, list_toop[i][j], x[j], y[i] + enteghali,
                                                       width, height, images);
                                        }

                                    }
                                    double angle = atan2(normalizedMouseX - 503, 740 - normalizedMouseY) * 180 /
                                                   M_PI; // Calculate the angle based on mouse position
                                    //cout<<angle<<endl;
                                    image = images[21].first; // Get the image from the vector based on its index
                                    destinationRect = {443, 685, 110,
                                                       200}; // Define the destination rectangle with dimensions 80x80
                                    SDL_Point center = {55,
                                                        100}; // Set the center of rotation to the center of the rectangle
                                    SDL_RenderCopyEx(m_renderer, image, NULL, &destinationRect, angle, &center,
                                                     SDL_FLIP_NONE); // Render the image at the specified coordinates and dimensions with rotation based on mouse position
                                    angle = atan2(normalizedMouseX - (470 + .04 * width),
                                                  745 + .04 * width - normalizedMouseY) * 180 / M_PI;
                                    line_cannon(m_renderer, 498, 785, normalizedMouseX, normalizedMouseY, 20,
                                                10, width);
                                    image = tasavir[6].first; // Get the image from the vector based on its index //تصویر تنظیمات بازی
                                    destinationRect = {p.x[0], p.y[11], 80,
                                                       80}; // Define the destination rectangle
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); // Render the image at the specified coordinates and dimensions
                                    image = tasavir[46].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر خروج یا اگزیت
                                    destinationRect = {80, 770, 100,
                                                       100}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                    image = tasavir[25].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر خروج یا اگزیت
                                    destinationRect = {820, 770, 45,
                                                       45}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه

                                    SDL_RenderPresent(m_renderer);

                                }
                                in_cannon = out_cannon;
                                out_cannon = cannon_random(list_toop, normalizedMouseX);
//                                cout<<out_cannon;
                            }
                            if((event_1.key.keysym.sym == SDLK_LSHIFT || event_1.key.keysym.sym == SDLK_RSHIFT )&& laser>0){
                                power=1 ;
                            }
                            if (event_1.type == SDL_MOUSEBUTTONDOWN) {
                                SDL_GetMouseState(&mouseX, &mouseY);
                                if ((mouseX - (200 + .04 * width)) * (mouseX - (200 + .04 * width)) +(mouseY - (800 + .04 * width)) * (mouseY - (800 + .04 * width)) <=(.04 * width) * (.04 * width))
                                    swap(in_cannon, out_cannon);
                                if(power == 1) {
                                    point -= 50;
                                    p_m += 1;

                                    //laser***************
                                    int stoon;
                                    if (mouseX < x[0])
                                        stoon = 0;
                                    if (mouseX > x[0] && mouseX < x[1])
                                        stoon = 1;
                                    if (mouseX > x[1] && mouseX < x[2])
                                        stoon = 2;
                                    if (mouseX > x[2] && mouseX < x[3])
                                        stoon = 3;
                                    if (mouseX > x[3] && mouseX < x[4])
                                        stoon = 4;
                                    if (mouseX > x[4] && mouseX < x[5])
                                        stoon = 5;
                                    if (mouseX > x[5] && mouseX < x[6])
                                        stoon = 6;
                                    if (mouseX > x[6] && mouseX < x[7])
                                        stoon = 7;
                                    if (mouseX > x[7] && mouseX < x[8])
                                        stoon = 8;
                                    if (mouseX > x[8] && mouseX < x[9])
                                        stoon = 9;
                                    if (mouseX > x[9])
                                        stoon = 9;
                                    image = tasavir[47].first; // Get the image from the vector based on its index //تصویر تنظیمات بازی
                                    destinationRect = {mouseX, mouseY, 40, 150}; // Define the destination rectangle
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); // Render the image at the specified coordinates and dimensions
                                    boxRGBA(m_renderer,mouseX,mouseY,mouseX+40,0,250,163,22,255);
                                    SDL_RenderPresent(m_renderer);
                                    SDL_Delay(500);
                                    for (int i = 1; i < 13; i++) {
                                        list_toop[i][stoon] = 0;
                                    }
                                    power = 0;

                                }
                                //********************** laser
                            }
                            if (event_1.type == SDL_QUIT) {
                                exit = false; // خروج از حلقه در صورت بستن پنجره
                            }
                            if (event_1.type == SDL_KEYDOWN && event_1.key.keysym.sym == SDLK_ESCAPE) {
                                mouseX = 34;// خروج از حلقه در صورت فشردن دکمه ESC
                                mouseY = 815;
                            }
                            if (event_1.type == SDL_MOUSEWHEEL) {
                                if (event_1.wheel.y > 0 && volume < 128) {
                                    volume += 4; // Scroll right

                                } else if (event_1.wheel.y < 0 && volume > 0) {
                                    volume -= 4; // Scroll left
                                }
//                                            cout << volume << endl;

                            }
//                                    ofstream fout("C:\\function\\data.txt",ios::app);
//                                    for(int o = 0 ; o<13 ; o++) {
//                                        for(int z = 0 ; z<10 ; z++) {
//                                            fout<<list_toop[o][z]<<" ";
//                                        }
//                                        fout<<endl ;
//                                    }
//                                    fout.close();
                        }
                        image = tasavir[6].first; // Get the image from the vector based on its index //تصویر تنظیمات بازی
                        destinationRect = {p.x[0], p.y[11], 80, 80}; // Define the destination rectangle
                        SDL_RenderCopy(m_renderer, image, NULL,
                                       &destinationRect); // Render the image at the specified coordinates and dimensions
                        image = tasavir[25].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر خروج یا اگزیت
                        destinationRect = {820, 770, 45, 45}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                        SDL_RenderCopy(m_renderer, image, NULL,
                                       &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                        image = images[in_cannon -1].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر مود های بازی
                        destinationRect = {x_ball, y_ball, .08 * width,
                                           .08 * width}; // مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                        center = {34, 0}; // Set the center of rotation to the center of the rectangle
                        SDL_RenderCopyEx(m_renderer, image, NULL, &destinationRect, angle, &center,
                                         SDL_FLIP_NONE); // Render the image at the specified coordinates and dimensions with rotation based on mouse position
                        image = images[out_cannon -1].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر مود های بازی
                        destinationRect = {200, 800, .08 * width,
                                           .08 * width}; // مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                        SDL_RenderCopy(m_renderer, image, NULL,
                                       &destinationRect); // تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                        aalineRGBA(m_renderer, .2 * width - .05 * width, .05 * width + 10 * fasele_do_dayere,
                                   width, .05 * width + 10 * fasele_do_dayere, 255, 255, 255, 255);
                        aalineRGBA(m_renderer, .2 * width - .05 * width, 0, .2 * width - .05 * width,
                                   .05 * width + 10 * fasele_do_dayere, 255, 255, 255, 255);
                        if (pause &&
                            pow((mouseX - (p.x[0] + 80 / 2)), 2) + pow((mouseY - (p.y[11] + 80 / 2)), 2) <=
                            1600) {
                            if (counter_Setting == 0) {
                                SDL_RenderClear(m_renderer);
                                image = tasavir[24].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه //تصویر پس زمینه
                                destinationRect = {0, 0, 900,
                                                   900}; // اینجا تصویر پس زمینه شروع بازی تعریف و قرار میگیره
                                SDL_RenderCopy(m_renderer, image, NULL,
                                               &destinationRect); // تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                SDL_RenderPresent(m_renderer);
                                SDL_Delay(500);
                                counter_Setting = 1;
                            }

                            //SDL_RenderClear(m_renderer); // پاک کردن صفحه
                            //گر اگزیت کلیک شد اگزیت به فالس تبدیل میشه و کانتر ستینگ برابر با صفر شود در انتها
                            //SDL_Delay(2000);
                            image = tasavir[18].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه //تصویر ااولین اهنگ
                            destinationRect = {p.x[0], p.y[2], 300,
                                               300}; // اینجا تصویر پس زمینه شروع بازی تعریف و قرار میگیره
                            SDL_RenderCopy(m_renderer, image, NULL,
                                           &destinationRect); // تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                            image = tasavir[19].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر دملین اهنگ
                            destinationRect = {p.x[1], p.y[2], 300,
                                               300}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                            SDL_RenderCopy(m_renderer, image, NULL,
                                           &destinationRect); // تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                            image = tasavir[20].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر سومین اهنگ
                            destinationRect = {p.x[2], p.y[2], 300,
                                               300}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                            SDL_RenderCopy(m_renderer, image, NULL,
                                           &destinationRect); // تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                            image = tasavir[21].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر چهارمین اهنگ
                            destinationRect = {p.x[0], p.y[6], 300,
                                               300}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                            SDL_RenderCopy(m_renderer, image, NULL,
                                           &destinationRect); // تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                            image = tasavir[22].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر پنجمین اهنگ
                            destinationRect = {p.x[1], p.y[6], 300,
                                               300}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                            SDL_RenderCopy(m_renderer, image, NULL,
                                           &destinationRect); // تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                            image = tasavir[23].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تتصویر ششمین اهنگ
                            destinationRect = {p.x[2], p.y[6], 300,
                                               300}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                            SDL_RenderCopy(m_renderer, image, NULL,
                                           &destinationRect); // تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                            image = tasavir[7].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر تنظیم حجم صدا
                            destinationRect = {375, 750, 206, 50}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                            SDL_RenderCopy(m_renderer, image, NULL,
                                           &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                            image = tasavir[25].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر خروج یا اگزیت
                            destinationRect = {820, 770, 45, 45}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                            SDL_RenderCopy(m_renderer, image, NULL,
                                           &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                            SDL_RenderPresent(m_renderer);
                            SDL_Event Event;
                            while (pause) {
                                Mix_VolumeMusic(volume);
                                if (SDL_PollEvent(&Event)) {
                                    if (Event.type == SDL_MOUSEBUTTONDOWN) {
                                        int mouse_X2, mouse_Y2;
                                        SDL_GetMouseState(&mouse_X2, &mouse_Y2);
                                        if (mouse_X2 >= p.x[0] && mouse_X2 <= p.x[0] + 300 &&
                                            mouse_Y2 >= p.y[2] && mouse_Y2 <= p.y[2] + 300) {
                                            music_num = 1;
                                            Mix_HaltMusic();
                                            play_music(musics, music_num, volume);
                                        }
                                        if (mouse_X2 >= p.x[1] && mouse_X2 <= p.x[1] + 300 &&
                                            mouse_Y2 >= p.y[2] && mouse_Y2 <= p.y[2] + 300) {
                                            music_num = 2;
                                            Mix_HaltMusic();
                                            play_music(musics, music_num, volume);

                                        }
                                        if (mouse_X2 >= p.x[2] && mouse_X2 <= p.x[2] + 300 &&
                                            mouse_Y2 >= p.y[2] && mouse_Y2 <= p.y[2] + 300) {
                                            music_num = 3;
                                            Mix_HaltMusic();
                                            play_music(musics, music_num, volume);

                                        }
                                        if (mouse_X2 >= p.x[0] && mouse_X2 <= p.x[0] + 300 &&
                                            mouse_Y2 >= p.y[6] && mouse_Y2 <= p.y[6] + 300) {
                                            music_num = 4;
                                            Mix_HaltMusic();
                                            play_music(musics, music_num, volume);

                                        }
                                        if (mouse_X2 >= p.x[1] && mouse_X2 <= p.x[1] + 300 &&
                                            mouse_Y2 >= p.y[6] && mouse_Y2 <= p.y[6] + 300) {
                                            music_num = 5;
                                            Mix_HaltMusic();
                                            play_music(musics, music_num, volume);

                                        }
                                        if (mouse_X2 >= p.x[2] && mouse_X2 <= p.x[2] + 300 &&
                                            mouse_Y2 >= p.y[6] && mouse_Y2 <= p.y[6] + 300) {
                                            music_num = 6;
                                            Mix_HaltMusic();
                                            play_music(musics, music_num, volume);
                                        }
                                        //گر اگزیت کلیک شد اگزیت به فالس تبدیل میشه و کانتر ستینگ برابر با صفر شود در انتها
                                        if (mouse_X2 >= 820 && mouse_X2 <= 820 + 45 && mouse_Y2 >= 770 &&
                                            mouse_Y2 <= 770 + 45) {
                                            pause = false;
                                            counter_Setting = 0;
                                        }
                                    }
                                    if (Event.type == SDL_KEYDOWN && Event.key.keysym.sym == SDLK_ESCAPE) {
                                        pause = false;
                                        counter_Setting = 0;
                                    }
                                    if (Event.type == SDL_MOUSEWHEEL) {
                                        if (Event.wheel.y > 0 && volume < 128) {
                                            volume += 4; // Scroll right

                                        } else if (Event.wheel.y < 0 && volume > 0) {
                                            volume -= 4; // Scroll left
                                        }
//                                        cout << volume << endl;
                                        Mix_VolumeMusic(volume);

                                    }
                                }

                                if (volume < 12) {
                                    boxRGBA(m_renderer, 377, 757, 397, 787, 255, 255, 255, 255);
                                }
                                if (volume < 24) {
                                    boxRGBA(m_renderer, 397, 757, 397, 787, 255, 255, 255, 255);
                                }
                                if (volume < 36) {
                                    boxRGBA(m_renderer, 417, 757, 397, 787, 255, 255, 255, 255);
                                }
                                if (volume < 48) {
                                    boxRGBA(m_renderer, 437, 757, 397, 787, 255, 255, 255, 255);
                                }
                                if (volume < 60) {
                                    boxRGBA(m_renderer, 457, 757, 397, 787, 255, 255, 255, 255);
                                }
                                if (volume < 74) {
                                    boxRGBA(m_renderer, 477, 757, 397, 787, 255, 255, 255, 255);
                                }
                                if (volume < 88) {
                                    boxRGBA(m_renderer, 497, 757, 397, 787, 255, 255, 255, 255);
                                }
                                if (volume < 102) {
                                    boxRGBA(m_renderer, 517, 757, 397, 787, 255, 255, 255, 255);
                                }
                                if (volume < 116) {
                                    boxRGBA(m_renderer, 537, 757, 397, 787, 255, 255, 255, 255);
                                }
                                if (volume < 129) {
                                    boxRGBA(m_renderer, 557, 757, 397, 787, 255, 255, 255, 255);
                                    boxRGBA(m_renderer, 577, 757, 397, 787, 255, 255, 255, 255);
                                }
                                if (volume > 12) {
                                    image = tasavir[8].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر اولین حجم صدا
                                    destinationRect = {377, 757, 20,
                                                       30}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                }
                                if (volume > 24) {
                                    image = tasavir[10].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر اولین حجم صدا
                                    destinationRect = {397, 757, 20,
                                                       30}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                }

                                if (volume > 36) {
                                    image = tasavir[11].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر اولین حجم صدا
                                    destinationRect = {417, 757, 20,
                                                       30}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                }

                                if (volume > 48) {
                                    image = tasavir[12].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر اولین حجم صدا
                                    destinationRect = {437, 757, 20,
                                                       30}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                }

                                if (volume > 60) {
                                    image = tasavir[12].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر اولین حجم صدا
                                    destinationRect = {457, 757, 20,
                                                       30}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                }

                                if (volume > 74) {
                                    image = tasavir[13].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر اولین حجم صدا
                                    destinationRect = {477, 757, 20,
                                                       30}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                }

                                if (volume > 88) {
                                    image = tasavir[14].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر اولین حجم صدا
                                    destinationRect = {497, 757, 20,
                                                       30}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                }

                                if (volume > 102) {
                                    image = tasavir[15].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر اولین حجم صدا
                                    destinationRect = {517, 757, 20,
                                                       30}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                }

                                if (volume > 116) {
                                    image = tasavir[16].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر اولین حجم صدا
                                    destinationRect = {537, 757, 20,
                                                       30}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                }

                                if (volume == 124 || volume == 128) {
                                    image = tasavir[17].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر اولین حجم صدا
                                    destinationRect = {557, 757, 20,
                                                       30}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                }

                                SDL_RenderPresent(m_renderer);
                                //تصویر تنظیمات
                            }
                            mouseX = 0;
                            mouseY = 0;
                        }
                        pause = true;
                        if (exit && mouseX >= 820 && mouseX <= 820 + 45 && mouseY >= 770 &&
                            mouseY <= 770 + 45) {
                            for (int i = 2; i < 13; i++) {
                                for (int j = 0; j < 10; j++) {
                                    list_toop[i][j] = 0;
                                }
                            }
                            mouseX = 0;
                            mouseY = 0;
                            exit = 0;
                        }
                        point=bonus.size();//محاسبه امتیاز
                        //***************************************
                        //خط های دور صفحه
//                        cout<<random_line_for_mode<<endl;
                        SDL_Event event3;
                        int m_x, m_y;
                        if(out_cannon==0) {
                            while (exit) {
                                image = tasavir[45].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر خروج یا اگزیت
                                destinationRect = {0, 0, 900, 900}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                SDL_RenderCopy(m_renderer, image, NULL,
                                               &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                image = tasavir[35].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر خروج یا اگزیت
                                destinationRect = {280, 50, 250, 60}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                SDL_RenderCopy(m_renderer, image, NULL,
                                               &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                image = tasavir[25].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر خروج یا اگزیت
                                destinationRect = {820, 770, 45,
                                                   45}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                SDL_RenderCopy(m_renderer, image, NULL,
                                               &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                if (SDL_PollEvent(&event3)) {
                                    if (event3.type == SDL_MOUSEBUTTONDOWN) {
                                        SDL_GetMouseState(&m_x, &m_y);
                                        if (m_x >= 820 && m_x <= 820 + 45 && m_y >= 770 && m_y <= 770 + 45) {
                                            exit = false;
                                        }
                                    }
                                }
                                string pouan = to_string(point);
                                SDL_Color textColor = {0, 0, 0};
                                SDL_Surface *textSurface = TTF_RenderText_Solid(font, pouan.c_str(), textColor);
                                SDL_Texture *textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
                                int textWidth = pouan.length() * 10, textHeight = 180;
                                TTF_SizeText(font, pouan.c_str(), &textWidth, &textHeight);
                                SDL_Rect textRect = {510, 65, textWidth, textHeight};
                                SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect);
                                SDL_RenderPresent(m_renderer);
                                out_cannon=+1;
                                for (int i = 0; i < 13; i++) {
                                    for (int j = 0; j < 10; j++) {
                                        list_toop[i][j] = 0;
                                    }
                                }
                            }
                            exit = true ;
                        }

                        for (int j = 0; j < 10; j++) {//خطی که برای سوختن استفاده شد .
                            if (list_toop[12][j] != 0) {
                                for (int i = 0; i < 13; i++) {
                                    for (int j = 0; j < 10; j++) {
                                        list_toop[i][j] = 0;
                                    }
                                }
//                                ofstream fout("C:\\function\\pointdata\\3.txt", ios::out);
//                                sort_list(mode3, userInput, point);
//                                for (int i = 0; i < mode3.size(); i++) {
//                                    fout << mode3[i] << endl;
//                                }
//                                fout.close();

                                SDL_Event event3;
                                int m_x, m_y;
                                while (exit) {
                                    image = tasavir[36].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر خروج یا اگزیت
                                    destinationRect = {0, 0, 900,900}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                    image = tasavir[35].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر خروج یا اگزیت
                                    destinationRect = {280, 400, 250,60}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                    image = tasavir[25].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر خروج یا اگزیت
                                    destinationRect = {820, 770, 45,
                                                       45}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                                    SDL_RenderCopy(m_renderer, image, NULL,
                                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                                    if (SDL_PollEvent(&event3)) {
                                        if (event3.type == SDL_MOUSEBUTTONDOWN) {
                                            SDL_GetMouseState(&m_x, &m_y);
                                            if (m_x >= 820 && m_x <= 820 + 45 && m_y >= 770 &&m_y <= 770 + 45) {
                                                exit = false;
                                            }
                                        }
                                    }
                                    string pouan = to_string(point);
                                    SDL_Color textColor = {0, 0, 0};
                                    SDL_Surface* textSurface = TTF_RenderText_Solid(font, pouan.c_str(), textColor);
                                    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
                                    int textWidth= pouan.length()*10, textHeight=180;
                                    TTF_SizeText(font, pouan.c_str(), &textWidth, &textHeight);
                                    SDL_Rect textRect = {510, 415, textWidth, textHeight};
                                    SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect);
                                    SDL_RenderPresent(m_renderer);
                                }
                                break ;
                            }
                        }
                        SDL_RenderPresent(m_renderer);

                    }

                }


            }
            //تصویر استارت بازی
            if (mouseX >= p.x[1] && mouseX <= p.x[1] + (width / 3) && mouseY >= p.y[4] &&mouseY <= p.y[4] + (height / 9)) {
                while(exit) {
                    image = tasavir[0].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر شروع بازی
                    destinationRect = {0, 0, 900, 900}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                    SDL_RenderCopy(m_renderer, image, NULL,
                                   &destinationRect); // تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                    image = tasavir[25].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر شروع بازی
                    destinationRect = {820, 770, 45, 45}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                    SDL_RenderCopy(m_renderer, image, NULL,&destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                    image = tasavir[37].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر شروع بازی
                    destinationRect = {50, 400, 250, 100}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                    SDL_RenderCopy(m_renderer, image, NULL,&destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                    image = tasavir[38].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر شروع بازی
                    destinationRect = {300, 400, 250, 100}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                    SDL_RenderCopy(m_renderer, image, NULL,&destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                    image = tasavir[39].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر شروع بازی
                    destinationRect = {550, 400, 250, 100}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                    SDL_RenderCopy(m_renderer, image, NULL,&destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                    SDL_RenderPresent(m_renderer);
                    SDL_Event Event_3;
                    int mouse_X3, mouse_Y3;
                    if (SDL_PollEvent(&Event_3)) {
                        if (Event_3.type==SDL_MOUSEBUTTONDOWN ) {
                            SDL_GetMouseState(&mouse_X3, &mouse_Y3);
                            if (mouse_X3 >= 50 && mouse_X3 <= 300 && mouse_Y3 >= 400 && mouse_Y3 <= 500){
                                modes=1;
                            }
                            if (mouse_X3 >= 300 && mouse_X3 <= 550 && mouse_Y3 >= 400 && mouse_Y3 <= 550){
                                modes=2;
                            }
                            if (mouse_X3 >= 550 && mouse_X3 <= 700 && mouse_Y3 >= 400 && mouse_Y3 <= 500){
                                modes = 3;
                            }
                            if (mouse_X3 >= 820 && mouse_X3 <= 820 + 45 && mouse_Y3 >= 770 && mouse_Y3 <= 770 + 45){
                                exit = false;
                            }
                        }
                    }
                }
            }//تصویر مود های بازی
            if (exit &&mouseX >= p.x[1] && mouseX <= p.x[1] + (width / 3) && mouseY >= p.y[6] &&mouseY <= p.y[6] + (height / 9)) {





                //********************
                while(exit) {
                    image = tasavir[0].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر شروع بازی
                    destinationRect = {0, 0, 900, 900}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                    SDL_RenderCopy(m_renderer, image, NULL,
                                   &destinationRect); // تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                    image = tasavir[32].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر شروع بازی
                    destinationRect = {50, 50, 250, 800}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                    SDL_RenderCopy(m_renderer, image, NULL,
                                   &destinationRect); // تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                    image = tasavir[33].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر شروع بازی
                    destinationRect = {350, 50, 250, 800}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                    SDL_RenderCopy(m_renderer, image, NULL,
                                   &destinationRect); // تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                    image = tasavir[34].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر شروع بازی
                    destinationRect = {650, 50, 250, 800}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                    SDL_RenderCopy(m_renderer, image, NULL,
                                   &destinationRect); // تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                    image = tasavir[25].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر شروع بازی
                    destinationRect = {820, 770, 45, 45}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                    SDL_RenderCopy(m_renderer, image, NULL,
                                   &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
////                    string full_name, name_p, point_p, dir_file;
////                    ifstream fin("C:\\function\\pointdata\\1.txt", ios::in);
//
//                    for (int j = 0; j < 19; j++) {
////                        getline(fin, full_name);
////                                cout<<full_name<<endl;
//                        int char_counter = 0;
//                        while(full_name[char_counter]!='+'){
//                            char char_name=full_name[char_counter];
//                            name_p[char_counter]+=char_name;
//                            char_counter++;
//                        }
//                        char_counter++;
//                        while(char_counter<full_name.length()){
//                            char char_name=full_name[char_counter];
//                            char_counter++;
//                            point_p+=char_name;
//                        }
//                        SDL_Color textColor = {0, 0, 0};
//                        SDL_Surface *textSurface = TTF_RenderText_Solid(font, name_p.c_str(), textColor);
//                        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
//                        int textWidth = name_p.length() * 10, textHeight = 100;
//                        TTF_SizeText(font, name_p.c_str(), &textWidth, &textHeight);
//                        SDL_Rect textRect = {1 * 300 + 180, j * 35 + 182, textWidth, textHeight};
//                        SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect);
//                        //******************
//                        textColor = {0, 0, 0};
//                        textSurface = TTF_RenderText_Solid(font, point_p.c_str(), textColor);
//                        textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
//                        textWidth = point_p.length() * 10, textHeight = 100;
//                        TTF_SizeText(font, point_p.c_str(), &textWidth, &textHeight);
//                        textRect = {1*300+100, j*35+182, textWidth, textHeight};
//                        SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect);
//                    }
//                    fin.close();
                    SDL_RenderPresent(m_renderer);
                    SDL_Event Event_3;
                    int mouse_X3, mouse_Y3;
                    if (SDL_PollEvent(&Event_3)) {
                        if (Event_3.type == SDL_MOUSEBUTTONDOWN) {
                            SDL_GetMouseState(&mouse_X3, &mouse_Y3);
                            if (mouse_X3 >= 820 && mouse_X3 <= 820 + 45 && mouse_Y3 >= 770 &&
                                mouse_Y3 <= 770 + 45) {
                                exit = false;
                            }

                        }
                    }
                }
//
            }//تصویر جدول امتیازات
            if (exit && mouseX >= p.x[1] && mouseX <= p.x[1] + (width / 3) && mouseY >= p.y[8] &&mouseY <= p.y[8] + (height / 9)) {
                while(exit) {
                    boxRGBA(m_renderer,0,0,900,900,128,128,128,255);
                    thickLineRGBA(m_renderer,0,500,900,500,20,0,0,0,255);
                    boxRGBA(m_renderer,0,500,900,900,r,g,b,255);
                    image = tasavir[25].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر شروع بازی
                    destinationRect = {820, 770, 45, 45}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                    SDL_RenderCopy(m_renderer, image, NULL,&destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                    image = tasavir[40].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر شروع بازی
                    destinationRect = {50, 200, 250, 100}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                    SDL_RenderCopy(m_renderer, image, NULL,&destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                    image = tasavir[41].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر شروع بازی
                    destinationRect = {300, 200, 250, 100}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                    SDL_RenderCopy(m_renderer, image, NULL,&destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                    image = tasavir[42].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر شروع بازی
                    destinationRect = {550, 200, 250, 100}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                    SDL_RenderCopy(m_renderer, image, NULL,&destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                    image = tasavir[7].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر شروع بازی
                    destinationRect = {50, 350, 250, 47}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                    SDL_RenderCopy(m_renderer, image, NULL,&destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                    image = tasavir[7].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر شروع بازی
                    destinationRect = {300, 350, 250, 47}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                    SDL_RenderCopy(m_renderer, image, NULL,&destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                    image = tasavir[7].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر شروع بازی
                    destinationRect = {550, 350, 250, 47}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                    SDL_RenderCopy(m_renderer, image, NULL,&destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                    image = tasavir[43].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر شروع بازی
                    destinationRect = {x_1, y_1, 20, 47}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                    SDL_RenderCopy(m_renderer, image, NULL,&destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                    image = tasavir[43].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر شروع بازی
                    destinationRect = {x_2, y_2, 20, 47}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                    SDL_RenderCopy(m_renderer, image, NULL,&destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                    image = tasavir[43].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر شروع بازی
                    destinationRect = {x_3, y_3, 20, 47}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                    SDL_RenderCopy(m_renderer, image, NULL,&destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه

                    SDL_Event Event_3;
                    int mouse_X3, mouse_Y3;
                    if (SDL_PollEvent(&Event_3)) {
                        if (Event_3.type==SDL_MOUSEBUTTONDOWN ) {
                            SDL_GetMouseState(&mouse_X3, &mouse_Y3);
                            if (mouse_X3 >= 30 && mouse_X3 <= 280 && mouse_Y3 >= 350 && mouse_Y3 <= 397){
                                x_1 = mouse_X3 ;
                                r=mouse_X3-30;
                            }
                            if (mouse_X3 >= 280 && mouse_X3 <= 530 && mouse_Y3 >= 350 && mouse_Y3 <= 397){
                                x_2=mouse_X3;
                                g=mouse_X3-280;
                            }
                            if (mouse_X3 >= 530 && mouse_X3 <= 780 && mouse_Y3 >= 350 && mouse_Y3 <= 397){
                                x_3 = mouse_X3;
                                b= mouse_X3 -530;
                            }
                            if (mouse_X3 >= 820 && mouse_X3 <= 820 + 45 && mouse_Y3 >= 770 && mouse_Y3 <= 770 + 45){
                                exit = false;
                            }
                        }
                    }
                    SDL_RenderPresent(m_renderer);
                }

            }//تصویر تم های بازی
            if (exit && mouseX >= p.x[1] && mouseX <= p.x[1] + (width / 3) && mouseY >= p.y[10] &&mouseY <= p.y[10] + (height / 9)) {
                boxRGBA(m_renderer,0,0,900,900,150,150,250,255);
                SDL_Event Event;
                while (exit) {
                    if (SDL_PollEvent(&Event)) {
                        if (Event.type == SDL_MOUSEBUTTONDOWN) {
                            int mouse_X2, mouse_Y2;
                            SDL_GetMouseState(&mouse_X2, &mouse_Y2);
                            if (mouse_X2 >= 820 && mouse_X2 <= 820 + 45 && mouse_Y2 >= 770 &&
                                mouse_Y2 <= 770 + 45) {
                                exit = false;
                                counter_Setting = 0;
                            }
                        }
                        image = tasavir[26].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر شروع بازی
                        destinationRect = {p.x[0], p.y[2], 300, 400}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                        SDL_RenderCopy(m_renderer, image, NULL,
                                       &destinationRect); // تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                        image = tasavir[27].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر شروع بازی
                        destinationRect = {p.x[2], p.y[2], 300, 400}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                        SDL_RenderCopy(m_renderer, image, NULL,
                                       &destinationRect); // تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                        image = tasavir[25].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر شروع بازی
                        destinationRect = {820, 770, 45, 45}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                        SDL_RenderCopy(m_renderer, image, NULL,
                                       &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                        image = tasavir[30].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر شروع بازی
                        destinationRect = {p.x[1], 200, 300, 50}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                        SDL_RenderCopy(m_renderer, image, NULL,
                                       &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                        image = tasavir[29].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر شروع بازی
                        destinationRect = {50+p.x[2], 500, 200, 100}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                        SDL_RenderCopy(m_renderer, image, NULL,
                                       &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                        image = tasavir[31].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر شروع بازی
                        destinationRect = {p.x[1], 400, 300, 50}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                        SDL_RenderCopy(m_renderer, image, NULL,
                                       &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                        image = tasavir[28].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر شروع بازی
                        destinationRect = {50+p.x[0], 500, 200, 100}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                        SDL_RenderCopy(m_renderer, image, NULL,
                                       &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه

                    }
                    SDL_RenderPresent(m_renderer);
                }



            }//تصویر سازندگان بازی
            if (exit &&pow((mouseX - (p.x[0] + 80 / 2)), 2) + pow((mouseY - (p.y[11] + 80 / 2)), 2) <= 1600) {

                if (counter_Setting == 0) {
                    SDL_RenderClear(m_renderer);
                    image = tasavir[24].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه //تصویر پس زمینه
                    destinationRect = {0, 0, 900,900}; // اینجا تصویر پس زمینه شروع بازی تعریف و قرار میگیره
                    SDL_RenderCopy(m_renderer, image, NULL,&destinationRect); // تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                    SDL_RenderPresent(m_renderer);
                    SDL_Delay(1000);
                    counter_Setting = 1;
                }

                //SDL_RenderClear(m_renderer); // پاک کردن صفحه
                //گر اگزیت کلیک شد اگزیت به فالس تبدیل میشه و کانتر ستینگ برابر با صفر شود در انتها
                //SDL_Delay(2000);
                image = tasavir[18].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه //تصویر ااولین اهنگ
                destinationRect = {p.x[0], p.y[2], 300,
                                   300}; // اینجا تصویر پس زمینه شروع بازی تعریف و قرار میگیره
                SDL_RenderCopy(m_renderer, image, NULL,
                               &destinationRect); // تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                image = tasavir[19].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر دملین اهنگ
                destinationRect = {p.x[1], p.y[2], 300,
                                   300}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                SDL_RenderCopy(m_renderer, image, NULL,
                               &destinationRect); // تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                image = tasavir[20].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر سومین اهنگ
                destinationRect = {p.x[2], p.y[2], 300,
                                   300}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                SDL_RenderCopy(m_renderer, image, NULL,
                               &destinationRect); // تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                image = tasavir[21].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر چهارمین اهنگ
                destinationRect = {p.x[0], p.y[6], 300,
                                   300}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                SDL_RenderCopy(m_renderer, image, NULL,
                               &destinationRect); // تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                image = tasavir[22].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر پنجمین اهنگ
                destinationRect = {p.x[1], p.y[6], 300,
                                   300}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                SDL_RenderCopy(m_renderer, image, NULL,
                               &destinationRect); // تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                image = tasavir[23].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تتصویر ششمین اهنگ
                destinationRect = {p.x[2], p.y[6], 300,
                                   300}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                SDL_RenderCopy(m_renderer, image, NULL,
                               &destinationRect); // تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                image = tasavir[7].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر تنظیم حجم صدا
                destinationRect = {375, 752, 206, 38}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                SDL_RenderCopy(m_renderer, image, NULL,
                               &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                image = tasavir[25].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر خروج یا اگزیت
                destinationRect = {820, 770, 45, 45}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                SDL_RenderCopy(m_renderer, image, NULL,
                               &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                SDL_RenderPresent(m_renderer);
                SDL_Event Event;
                while (exit) {
                    Mix_VolumeMusic(volume);
                    if (SDL_PollEvent(&Event)) {
                        if (Event.type==SDL_MOUSEBUTTONDOWN) {
                            int mouse_X2, mouse_Y2;
                            SDL_GetMouseState(&mouse_X2, &mouse_Y2);
                            if (mouse_X2 >= p.x[0] && mouse_X2 <= p.x[0] + 300 && mouse_Y2 >= p.y[2] && mouse_Y2 <= p.y[2] + 300 )
                            {
                                music_num = 1;
                                Mix_HaltMusic();
                                play_music(musics,music_num,volume);
                            }
                            if (mouse_X2 >= p.x[1] && mouse_X2 <= p.x[1] + 300 && mouse_Y2 >= p.y[2] && mouse_Y2 <= p.y[2] + 300 )
                            {
                                music_num = 2;
                                Mix_HaltMusic();
                                play_music(musics,music_num,volume);

                            }
                            if (mouse_X2 >= p.x[2] && mouse_X2 <= p.x[2] + 300 && mouse_Y2 >= p.y[2] && mouse_Y2 <= p.y[2] + 300 )
                            {
                                music_num = 3;
                                Mix_HaltMusic();
                                play_music(musics,music_num,volume);

                            }
                            if (mouse_X2 >= p.x[0] && mouse_X2 <= p.x[0] + 300 && mouse_Y2 >= p.y[6] && mouse_Y2 <= p.y[6] + 300 )
                            {
                                music_num = 4;
                                Mix_HaltMusic();
                                play_music(musics,music_num,volume);

                            }
                            if (mouse_X2 >= p.x[1] && mouse_X2 <= p.x[1] + 300 && mouse_Y2 >= p.y[6] && mouse_Y2 <= p.y[6] + 300 )
                            {
                                music_num = 5;
                                Mix_HaltMusic();
                                play_music(musics,music_num,volume);

                            }
                            if (mouse_X2 >= p.x[2] && mouse_X2 <= p.x[2] + 300 && mouse_Y2 >= p.y[6] && mouse_Y2 <= p.y[6] + 300 )
                            {
                                music_num = 6;
                                Mix_HaltMusic();
                                play_music(musics,music_num,volume);
                            }
                            //گر اگزیت کلیک شد اگزیت به فالس تبدیل میشه و کانتر ستینگ برابر با صفر شود در انتها
                            if (mouse_X2 >= 820 && mouse_X2 <= 820 + 45 && mouse_Y2 >= 770 && mouse_Y2 <= 770 + 45)
                            {
                                exit = false;
                                counter_Setting = 0;
                            }
                        }
                        if (Event.type == SDL_KEYDOWN && Event.key.keysym.sym == SDLK_ESCAPE) {
                            exit = false;
                            counter_Setting = 0;
                        }

                        if (Event.type == SDL_MOUSEWHEEL) {
                            if (Event.wheel.y > 0 && volume < 128) {
                                volume += 4; // Scroll right

                            } else if (Event.wheel.y < 0 && volume > 0) {
                                volume -= 4; // Scroll left
                            }
//                                        cout << volume << endl;
                            Mix_VolumeMusic(volume);

                        }
                    }

                    if (volume < 12) {
                        boxRGBA(m_renderer,377,757,397,787,255,255,255,255);
                    }
                    if (volume < 24){
                        boxRGBA(m_renderer,397,757,397,787,255,255,255,255);
                    }
                    if (volume < 36) {
                        boxRGBA(m_renderer,417,757,397,787,255,255,255,255);
                    }
                    if (volume < 48) {
                        boxRGBA(m_renderer,437,757,397,787,255,255,255,255);
                    }
                    if (volume < 60) {
                        boxRGBA(m_renderer,457,757,397,787,255,255,255,255);
                    }
                    if (volume < 74) {
                        boxRGBA(m_renderer,477,757,397,787,255,255,255,255);
                    }
                    if (volume < 88) {
                        boxRGBA(m_renderer,497,757,397,787,255,255,255,255);
                    }
                    if (volume < 102) {
                        boxRGBA(m_renderer,517,757,397,787,255,255,255,255);
                    }
                    if (volume < 116) {
                        boxRGBA(m_renderer,537,757,397,787,255,255,255,255);
                    }
                    if (volume < 129) {
                        boxRGBA(m_renderer,557,757,397,787,255,255,255,255);
                        boxRGBA(m_renderer,577,757,397,787,255,255,255,255);
                    }
                    if (volume > 12) {
                        image = tasavir[8].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر اولین حجم صدا
                        destinationRect = {377, 757, 20,
                                           30}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                        SDL_RenderCopy(m_renderer, image, NULL,
                                       &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                    }
                    if (volume > 24) {
                        image = tasavir[10].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر اولین حجم صدا
                        destinationRect = {397, 757, 20,
                                           30}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                        SDL_RenderCopy(m_renderer, image, NULL,
                                       &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                    }

                    if (volume > 36) {
                        image = tasavir[11].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر اولین حجم صدا
                        destinationRect = {417, 757, 20,
                                           30}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                        SDL_RenderCopy(m_renderer, image, NULL,
                                       &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                    }

                    if (volume > 48) {
                        image = tasavir[12].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر اولین حجم صدا
                        destinationRect = {437, 757, 20,
                                           30}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                        SDL_RenderCopy(m_renderer, image, NULL,
                                       &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                    }

                    if (volume > 60) {
                        image = tasavir[12].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر اولین حجم صدا
                        destinationRect = {457, 757, 20,
                                           30}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                        SDL_RenderCopy(m_renderer, image, NULL,
                                       &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                    }

                    if (volume > 74) {
                        image = tasavir[13].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر اولین حجم صدا
                        destinationRect = {477, 757, 20,
                                           30}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                        SDL_RenderCopy(m_renderer, image, NULL,
                                       &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                    }

                    if (volume > 88) {
                        image = tasavir[14].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر اولین حجم صدا
                        destinationRect = {497, 757, 20,
                                           30}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                        SDL_RenderCopy(m_renderer, image, NULL,
                                       &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                    }

                    if (volume > 102) {
                        image = tasavir[15].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر اولین حجم صدا
                        destinationRect = {517, 757, 20,
                                           30}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                        SDL_RenderCopy(m_renderer, image, NULL,
                                       &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                    }

                    if (volume > 116) {
                        image = tasavir[16].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر اولین حجم صدا
                        destinationRect = {537, 757, 20,
                                           30}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                        SDL_RenderCopy(m_renderer, image, NULL,
                                       &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                    }

                    if (volume == 124 || volume==128) {
                        image = tasavir[17].first; // تصویر را از وکتور حاوی تصاویر بر اساس شاخص و اصطلاحا index  اون دریافت میکنه  //تصویر اولین حجم صدا
                        destinationRect = {557, 757, 20,
                                           30}; //مکان و مختصات دکمه و مستطیل جدید تعریف میشه
                        SDL_RenderCopy(m_renderer, image, NULL,
                                       &destinationRect); //// تصویر  در مختصات و ابعاد مشخص شده رندر میشه
                    }

                    SDL_RenderPresent(m_renderer);
                    //تصویر تنظیمات
                }

            }
            exit= true ;
            if(mouseX >= 820 && mouseX <= 820 + 45 && mouseY >= 770 && mouseY <= 770 + 45){
                return 0 ;
            }
            SDL_RenderPresent(m_renderer);
        }

    }
}
void list_toop_ha(int list [13][10],double & enteghali,int width,int mouse_x,int mouse_y,int & random_line_mode ) { // از 13 ردیف دو ردیف در بالای صفحه و ردیف آخر در زیر border تعریف میشه
    if (enteghali > width * .08 ) {
        for (int i = 12; i > 0; i--) {
            swap(list[i], list[i - 1]);
            enteghali = 0.1;
        }
        if ((random_line_mode > 0 || random_line_mode == -1)) {

            for (int j = 0; j < 10; j++) {
                int zir_list[3];
                if (j == 0) {
                    zir_list[0] = 0;
                    zir_list[1] = list[1][j];
                    zir_list[2] = list[1][j + 1];
                } else if (j < 9) {
                    zir_list[0] = list[0][j - 1];
                    zir_list[1] = list[1][j];
                    zir_list[2] = list[1][j + 1];
                } else if (j == 9) {
                    zir_list[0] = list[0][j - 1];
                    zir_list[1] = list[1][j];
                    zir_list[2] = 0;
                }
                srand(j * time(0) - j + 10 * mouse_x - 4 * mouse_y);
                list[0][j] = random_line(zir_list);

            }
            if (random_line_mode == -1) {}
            else {
                random_line_mode--;
            }
        }
        else{
            for(int i = 0 ; i<10 ; i++)
                list[0][i]=80;
        }
    }
}
int cannon_random(int list[13][10],int mouse_x) {
    bool zirlist[7];
    for(int i = 0 ; i<7 ; i++)
        zirlist[i]=0;
    for(int i = 0 ;i<13 ; i++){
        for(int j = 0 ; j<10 ;j++) {
            switch(list[i][j]) {
                case 1 :
                    zirlist[1]=1;
                    break ;
                case 2 :
                    zirlist[2]=1;
                    break ;
                case 3 :
                    zirlist[3]=1;
                    break ;
                case 4 :
                    zirlist[4]=1;
                    break ;
                case 5 :
                    zirlist[5]=1;
                    break ;
                case 6 :
                    zirlist[2]=1;
                    zirlist[3]=1;
                    break ;
                case 7 :
                    zirlist[5]=1;
                    zirlist[3]=1;
                    break ;
                case 8 :
                    zirlist[4]=1;
                    zirlist[3]=1;
                    break ;
                case 9 :
                    zirlist[1]=1;
                    zirlist[3]=1;
                    break ;
                case 10 :
                    zirlist[1]=1;
                    zirlist[5]=1;
                    break ;
                case 11 :
                    zirlist[2]=1;
                    zirlist[5]=1;
                    break ;
                case 12 :
                    zirlist[4]=1;
                    zirlist[5]=1;
                    break ;
                case 13 :
                    zirlist[1]=1;
                    zirlist[2]=1;
                    break ;
                case 14 :
                    zirlist[1]=1;
                    zirlist[4]=1;
                    break ;
                case 15 :
                    zirlist[2]=1;
                    zirlist[4]=1;
                    break ;
                case 16 :
                    break;
                case 17 :
                    zirlist[1]=1;
                    break ;
                case 18 :
                    zirlist[3]=1;
                    break ;
                case 19 :
                    zirlist[2]=1;
                    break ;
                case 20 :
                    zirlist[4]=1;
                    break ;
                case 21 :
                    zirlist[5]=1;
                    break ;
                case 80 :
                    zirlist[6]=1;
                    break;

            }
        }
    }
    int counter = 0 ;
    for(int i = 1 ; i<=5 ; i++){
        if(zirlist[i]==1)
            counter++;
    }
    if (counter==0 && zirlist[6]==1)
        return 0 ;
    srand(mouse_x*time(0));
    if(counter>0) {
        int rand_num = rand() % counter + 1;
        int c = 0;
        while (rand_num > 0) {
            if (zirlist[c] == 1) {
                rand_num--;
            }
            c++;

        }
        return c - 1;


    }
}
void ball_green(SDL_Renderer * renderer,double x_center , double y_center, double width,std::vector<ImagePair> images){
    int x = x_center ; int y = y_center ; int width_1=width ;
    SDL_Texture* image = images[0].first; // Get the image from the vector based on its index
    SDL_Rect destinationRect = {x-.04* width, y, .08*width,.08*width}; // Define the destination rectangle
    SDL_RenderCopy(renderer, image, NULL, &destinationRect); // Render the image at the specified coordinates and dimensions


} //ball number 1
void ball_yellow(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images){
    int x = x_center ; int y = y_center ; int width_1=width ;
    SDL_Texture* image = images[1].first; // Get the image from the vector based on its index
    SDL_Rect destinationRect = {x-.04* width, y, .08*width,.08*width}; // Define the destination rectangle
    SDL_RenderCopy(renderer, image, NULL, &destinationRect); // Render the image at the specified coordinates and dimensions

}//ball number 2
void ball_red(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images){
    int x = x_center ; int y = y_center ; int width_1=width ;
    SDL_Texture* image = images[2].first; // Get the image from the vector based on its index
    SDL_Rect destinationRect = {x-.04* width, y, .08*width,.08*width}; // Define the destination rectangle
    SDL_RenderCopy(renderer, image, NULL, &destinationRect); // Render the image at the specified coordinates and dimensions

}//ball number 3
void ball_purple(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images){
    int x = x_center ; int y = y_center ; int width_1=width ;
    SDL_Texture* image = images[3].first; // Get the image from the vector based on its index
    SDL_Rect destinationRect = {x-.04* width, y, .08*width,.08*width}; // Define the destination rectangle
    SDL_RenderCopy(renderer, image, NULL, &destinationRect); // Render the image at the specified coordinates and dimensions

}//ball number 4
void ball_blue(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images){
    int x = x_center ; int y = y_center ; int width_1=width ;
    SDL_Texture* image = images[4].first; // Get the image from the vector based on its index
    SDL_Rect destinationRect = {x-.04* width, y, .08*width,.08*width}; // Define the destination rectangle
    SDL_RenderCopy(renderer, image, NULL, &destinationRect); // Render the image at the specified coordinates and dimensions

}//ball number 5
void ball_red_yellow(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images){
    int x = x_center ; int y = y_center ; int width_1=width ;
    SDL_Texture* image = images[5].first; // Get the image from the vector based on its index
    SDL_Rect destinationRect = {x-.04* width, y, .08*width,.08*width}; // Define the destination rectangle
    SDL_RenderCopy(renderer, image, NULL, &destinationRect); // Render the image at the specified coordinates and dimensions




}//ball number 6
void ball_red_blue(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images){
    int x = x_center ; int y = y_center ; int width_1=width ;
    SDL_Texture* image = images[6].first; // Get the image from the vector based on its index
    SDL_Rect destinationRect = {x-.04* width, y, .08*width,.08*width}; // Define the destination rectangle
    SDL_RenderCopy(renderer, image, NULL, &destinationRect); // Render the image at the specified coordinates and dimensions

}//ball number 7
void ball_red_purple(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images){
    int x = x_center ; int y = y_center ; int width_1=width ;
    SDL_Texture* image = images[7].first; // Get the image from the vector based on its index
    SDL_Rect destinationRect = {x-.04* width, y, .08*width,.08*width}; // Define the destination rectangle
    SDL_RenderCopy(renderer, image, NULL, &destinationRect); // Render the image at the specified coordinates and dimensions

}//ball number 8
void ball_red_green(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images){
    int x = x_center ; int y = y_center ; int width_1=width ;
    SDL_Texture* image = images[8].first; // Get the image from the vector based on its index
    SDL_Rect destinationRect = {x-.04* width, y, .08*width,.08*width}; // Define the destination rectangle
    SDL_RenderCopy(renderer, image, NULL, &destinationRect); // Render the image at the specified coordinates and dimensions

}//ball number 9
void ball_blue_green(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images){
    int x = x_center ; int y = y_center ; int width_1=width ;
    SDL_Texture* image = images[9].first; // Get the image from the vector based on its index
    SDL_Rect destinationRect = {x-.04* width, y, .08*width,.08*width}; // Define the destination rectangle
    SDL_RenderCopy(renderer, image, NULL, &destinationRect); // Render the image at the specified coordinates and dimensions

}//ball number 10
void ball_blue_yellow(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images){
    int x = x_center ; int y = y_center ; int width_1=width ;
    SDL_Texture* image = images[10].first; // Get the image from the vector based on its index
    SDL_Rect destinationRect = {x-.04* width, y, .08*width,.08*width}; // Define the destination rectangle
    SDL_RenderCopy(renderer, image, NULL, &destinationRect); // Render the image at the specified coordinates and dimensions

}//ball number 11
void ball_blue_purple(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images){
    int x = x_center ; int y = y_center ; int width_1=width ;
    SDL_Texture* image = images[11].first; // Get the image from the vector based on its index
    SDL_Rect destinationRect = {x-.04* width, y, .08*width,.08*width}; // Define the destination rectangle
    SDL_RenderCopy(renderer, image, NULL, &destinationRect); // Render the image at the specified coordinates and dimensions

}//ball number 12
void ball_green_yellow(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images){
    int x = x_center ; int y = y_center ; int width_1=width ;
    SDL_Texture* image = images[12].first; // Get the image from the vector based on its index
    SDL_Rect destinationRect = {x-.04* width, y, .08*width,.08*width}; // Define the destination rectangle
    SDL_RenderCopy(renderer, image, NULL, &destinationRect); // Render the image at the specified coordinates and dimensions

}//ball number 13
void ball_green_purple(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images){
    int x = x_center ; int y = y_center ; int width_1=width ;
    SDL_Texture* image = images[13].first; // Get the image from the vector based on its index
    SDL_Rect destinationRect = {x-.04* width, y, .08*width,.08*width}; // Define the destination rectangle
    SDL_RenderCopy(renderer, image, NULL, &destinationRect); // Render the image at the specified coordinates and dimensions

}//ball number 14
void ball_purple_yellow(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images){
    int x = x_center ; int y = y_center ; int width_1=width ;
    SDL_Texture* image = images[14].first; // Get the image from the vector based on its index
    SDL_Rect destinationRect = {x-.04* width, y, .08*width,.08*width}; // Define the destination rectangle
    SDL_RenderCopy(renderer, image, NULL, &destinationRect); // Render the image at the specified coordinates and dimensions

}//ball number 15
void ball_black(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images) {
    int x = x_center ; int y = y_center ; int width_1=width ;
    SDL_Texture* image = images[15].first; // Get the image from the vector based on its index
    SDL_Rect destinationRect = {x-.04* width, y, .08*width,.08*width}; // Define the destination rectangle
    SDL_RenderCopy(renderer, image, NULL, &destinationRect); // Render the image at the specified coordinates and dimensions

}//ball number 16
void ball_lock_green(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images){
    int x = x_center ; int y = y_center ; int width_1=width ;
    SDL_Texture* image = images[16].first; // Get the image from the vector based on its index
    SDL_Rect destinationRect = {x-.04* width, y, .08*width,.08*width}; // Define the destination rectangle
    SDL_RenderCopy(renderer, image, NULL, &destinationRect); // Render the image at the specified coordinates and dimensions

}//ball number 17
void ball_lock_red(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images){
    int x = x_center ; int y = y_center ; int width_1=width ;
    SDL_Texture* image = images[17].first; // Get the image from the vector based on its index
    SDL_Rect destinationRect = {x-.04* width, y, .08*width,.08*width}; // Define the destination rectangle
    SDL_RenderCopy(renderer, image, NULL, &destinationRect); // Render the image at the specified coordinates and dimensions

}//ball number 18
void ball_lock_yellow(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images){
    int x = x_center ; int y = y_center ; int width_1=width ;
    SDL_Texture* image = images[18].first; // Get the image from the vector based on its index
    SDL_Rect destinationRect = {x-.04* width, y, .08*width,.08*width}; // Define the destination rectangle
    SDL_RenderCopy(renderer, image, NULL, &destinationRect); // Render the image at the specified coordinates and dimensions

}//ball number 19
void ball_lock_purple(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images){
    int x = x_center ; int y = y_center ; int width_1=width ;
    SDL_Texture* image = images[19].first; // Get the image from the vector based on its index
    SDL_Rect destinationRect = {x-.04* width, y, .08*width,.08*width}; // Define the destination rectangle
    SDL_RenderCopy(renderer, image, NULL, &destinationRect); // Render the image at the specified coordinates and dimensions

}//ball number 20
void ball_lock_blue(SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images){
    int x = x_center ; int y = y_center ; int width_1=width ;
    SDL_Texture* image = images[20].first; // Get the image from the vector based on its index
    SDL_Rect destinationRect = {x-.04* width, y, .08*width,.08*width}; // Define the destination rectangle
    SDL_RenderCopy(renderer, image, NULL, &destinationRect); // Render the image at the specified coordinates and dimensions

}//ball number 21
void ball_happy (SDL_Renderer * renderer,double x_center , double y_center,double width,std::vector<ImagePair> images) {
    int x = x_center;
    int y = y_center;
    int width_1 = width;
    SDL_Texture *image = images[27].first; // Get the image from the vector based on its index
    SDL_Rect destinationRect = {x - .04 * width, y,  .1 * width, .1 * width}; // Define the destination rectangle
    SDL_RenderCopy(renderer, image, NULL,
                   &destinationRect); // Render the image at the specified coordinates and dimensions
}
void main_balls(SDL_Renderer * renderer,int a ,double x_center , double y_center,double width,double height,std::vector<ImagePair> images){//a نوع رنگ توپ است
    //visibility اگر 0 نمایش میده
    //اگر 1 همون جا محو میشه
    //اگه 2 میوفته زمین
    switch(a) {
        case 1: {
            ball_green(renderer, x_center, y_center, width,images);
            break;
        }
        case 2: {
            ball_yellow(renderer, x_center, y_center, width,images);
            break;
        }
        case 3: {
            ball_red(renderer, x_center, y_center, width,images);
            break;
        }
        case 4: {
            ball_purple(renderer, x_center, y_center, width,images);
            break;
        }
        case 5: {
            ball_blue(renderer, x_center, y_center, width,images);
            break;
        }
        case 6: {
            ball_red_yellow(renderer, x_center, y_center, width,images);
            break;
        }
        case 7: {
            ball_red_blue(renderer, x_center, y_center, width,images);
            break;
        }
        case 8: {
            ball_red_purple(renderer, x_center, y_center, width,images);
            break;
        }
        case 9: {
            ball_red_green(renderer, x_center, y_center, width,images);
            break;
        }
        case 10: {
            ball_blue_green(renderer, x_center, y_center, width,images);
            break;
        }
        case 11: {
            ball_blue_yellow(renderer, x_center, y_center, width,images);
            break;
        }
        case 12: {
            ball_blue_purple(renderer, x_center, y_center, width,images);
            break;
        }
        case 13: {
            ball_green_yellow(renderer, x_center, y_center, width,images);
            break;
        }
        case 14: {
            ball_green_purple(renderer, x_center, y_center, width,images);
            break;
        }
        case 15:{
            ball_purple_yellow(renderer, x_center, y_center, width,images);
            break;
        }
        case 16: {
            ball_black(renderer, x_center, y_center, width,images);
            break;
        }
        case 17: {
            ball_lock_green(renderer, x_center, y_center, width,images);
            break;
        }
        case 18: {
            ball_lock_red(renderer, x_center, y_center, width,images);
            break;
        }
        case 19: {
            ball_lock_yellow(renderer, x_center, y_center, width,images);
            break;
        }
        case 20: {
            ball_lock_purple(renderer, x_center, y_center, width,images);
            break;
        }
        case 21: {
            ball_lock_blue(renderer, x_center, y_center, width,images);
            break;
        }

    }
}
void first_second_line(line_1_2 &line) {
    for (int i = 0; i < 4; i++) {
        line.line_1[i] = rand() % 5 + 1;
        line.line_2[i] = rand() % 5 + 1;
    }
}
int random_line(int list [3]) {//تولید خطوط به صورت رندم
    balls_with_num balls ;
    int list_1[22];
    for(int i = 0 ; i<22 ; i++)
        list_1[i]=0 ;
    //****************
    //*********************************
    for(int i = 0 ; i<3 ; i++) {
        int random_num_between_0_100=0 ;
        int random_num;
        //**************************
        if (list[i]==0 ){
            random_num= rand()%5+1;
            return random_num;
        }
        //******************************
        random_num_between_0_100= rand()%100+1;
//        ofstream fout("C:\\function\\data.txt",ios::app) ;
//        fout<<random_num_between_0_100<<" ";
//        fout.close();
        if (list[i]<=5 && list[i]>=1) { //اگه توپ معمولی بود
            if (random_num_between_0_100 >= 0 && random_num_between_0_100 < 20)//20 درصد احتمال آمدن همون رنگ توپ
                list_1[list[i]] += 1;
            if (random_num_between_0_100 >= 20 && random_num_between_0_100 < 35) {//15 درصد احتمال اومدن توپ رنگی همون
                random_num = rand() % 5 + 1;
                list_1[balls.ball[list[i]][random_num]] += 1;
            }
            if (random_num_between_0_100 >= 35 && random_num_between_0_100 < 40) {//احتمال اومدن توپ قفل شده همون
                list_1[balls.ball[list[i]][5]] += 1;
            }
            if (random_num_between_0_100 >= 40) {//یک رنگ توپ ساده دیگه 60 درصد
                random_num = rand() % 5 + 1;
                if (random_num == 5)
                    list_1[16] += 1;
                else
                    list_1[random_num]+=1 ;
            }
        }//توپ های ساده
        if (list[i]>6 && list[i]<=15) {
            int ball_1 = 0, ball_2 = 0;
            for (int z = 1; z < 6; z++) {
                for (int o = 0; o < 6; o++) {
                    if (balls.ball[z][o] == list[i] && ball_1 == 0)
                        ball_1 = z;
                    else if (balls.ball[z][o] == list[i] && ball_1 != 0)
                        ball_2 = z;
                }
            }
            if (random_num_between_0_100 >= 0 && random_num_between_0_100 < 10)//10 درصد توپ رنگی اول
                list_1[ball_1] += 1;
            if (random_num_between_0_100 >= 10 && random_num_between_0_100 < 20)//10 درصد توپ رنگی دوم
                list_1[ball_2] += 1;
            if (random_num_between_0_100 >= 20 && random_num_between_0_100 < 40)// 20 درصد خودش
                list_1[list[i]] += 1;
            if (random_num_between_0_100 >= 40) {//50 درصد رندوم یه چیز دیگه
                random_num = rand() % 21 + 1;
                list_1[random_num] += 1;
            }
        } // توپ های دورنگ
        if (list[i]==16) {
            if (random_num_between_0_100 < 20)//20 درصد خودش
                list_1[16] += 1;
            if (random_num_between_0_100 >= 20 && random_num_between_0_100 < 100) {//80 درصد یه چیز دیگه
                random_num = rand() % 21 + 1;
                list_1[random_num] += 1;
            }
        }//توپ مشکی
        if(list[i]>16 && list[i]<=21) {
            if (random_num_between_0_100 <= 35) {//35 درصد خودش
                list_1[list[i]] += 1;
            }
            else if (random_num_between_0_100 < 45) {//10 درصد توپ ساده از خودش
                int ball_1 = 0;
                for (int z = 1; z < 6; z++) {
                    for (int o = 0; o < 6; o++) {
                        if (balls.ball[z][o] == list[i])
                            ball_1 = z;
                    }
                }
                list_1[ball_1] += 1;
            }
            if (random_num_between_0_100 > 45){//55 درصد یه چیز دیگه
                random_num = rand() % 21 + 1;
                list_1[random_num] += 1;
            }


        }//توپ قفل دار

    }
    int x_1=0 , x_2=0,x_3=0 ;
    for(int i = 0 ; i<22 ;i++) {
        if(list_1[i]>=2)//اگه دو عدد یکسان همون جا پایان
            return i;
        else if(list_1[i]==1 && x_1 ==0)
            x_1 = i;
        else if(list_1[i]==1 && x_1 !=0 && x_2 ==0 )
            x_2 = i ;
        else if(list_1[i]==1 && x_1 !=0)
            x_3 = i ;
    }
    //************************
    int color[3][2];
    int color_2 [6];
    for(int i = 0 ; i<6  ; i++)
        color_2[i]=0 ;
    for(int i = 0 ; i<3;i++)
        for(int j = 0 ; j<2 ; j++)
            color[i][j]=0 ;
    for (int z = 1; z < 6; z++) {
        for (int o = 0; o < 6; o++) {
            if (balls.ball[z][o] == x_1 && color[0][0] == 0)
                color[0][0] = z;
            else if (balls.ball[z][o] == x_2 && color[0][0] != 0 && color[1][0]==0)
                color[1][0] = z;
            else if (balls.ball[z][o] == x_3 && color[1][0] != 0)
                color[2][0] = z;
        }
    }
    //پیدا کردن رنگ یکسان
//********************************

    for (int z = 0; z < 3; z++) {
        color_2[color[z][0]]+=1 ;
    }
    for(int i = 0 ; i<6  ; i++){
        if(color_2[i]>=2 && i!=0)
            return i ;
    }
    //*********************
    int hazf_x = 0 ;
    if (x_3==0)
        hazf_x=1;
    int randnum = rand()%(3-hazf_x)+1;
    switch (randnum) {
        case 1 :
            return x_1 ;
        case 2:
            return x_2 ;
        case 3 :
            return x_3 ;
    }
    //اگه دو تا رنگ یکی هم ندیدیم یکی از بین اونا رندم انتخاب میکنیم
    //***********************

}
void play_music (vector<Mix_Music*>musics,int num , int volume) {
    Mix_PlayMusic(musics[num-1], -1);
    Mix_VolumeMusic(volume);

}
void my_line (SDL_Renderer *renderer , int x_1 , int y_1 ,int l , double teta , int width , int r , int g , int b  ) { // teta درجه است
    double x=(teta/180.0)*M_PI;
    int x_2 = x_1 + l* cos(x);
    int y_2 = y_1 - l* sin(x);
    thickLineRGBA(renderer ,x_1 , y_1 ,x_2,y_2 , width , r,g,b,255 );
}
void line_cannon(SDL_Renderer *m_renderer,int x1, int y1,double x2,double y2,int dashLength, int gapLength,int width ) {
    float lineLength = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    // Calculate the direction of the line
    float dx = (x2 - x1) / lineLength;
    float dy = (y2 - y1) / lineLength;
    // Draw the dashed line
    float currentLength = 0;
    bool drawingDash = true;
    while (currentLength < lineLength) {
        int x3 = x1 + currentLength * dx;
        int y3 = y1 + currentLength * dy;
        currentLength += drawingDash ? dashLength : gapLength;
        if (currentLength > lineLength) {
            currentLength = lineLength;
        }
        int x4 = x1 + currentLength * dx;
        int y4 = y1 + currentLength * dy;
        if (drawingDash) {
            aalineRGBA(m_renderer, x3, y3, x4, y4,255,255,255,255);
        }
        drawingDash = !drawingDash;
    }
}
void shoot_ball(std::vector<ImagePair> images,int in_cannon,int list_toop[13][10],SDL_Renderer *m_renderer,int x1, int y1,int x2,int y2,int width) {
    int v = 3;
    int x = x1 ;
    int y = y1 ;
    int vy = -1* abs(y2-y1);
    int vx = x2-x1 ;
    if(x>900 || x<0)
        vx=-1*vx;
    double zarib = v/sqrt(pow(vx,2)+pow(vy,2))/1.0 ;
    vx = vx*zarib;
    vy = vy*zarib ;
    while (y>0 ) {
        if(x>(900-(.04*width)) || x<.2*width)
            vx=-1*vx;
        x+=vx ;
        y+=vy ;
        SDL_Texture* image = images[in_cannon-1].first; // Get the image from the vector based on its index
        SDL_Rect destinationRect = {x,y, .08*width,.08*width}; // Define the destination rectangle
        SDL_RenderCopy(m_renderer, image, NULL, &destinationRect); // Render the image at the specified coordinates and dimensions
        SDL_RenderPresent(m_renderer);
        SDL_RenderClear(m_renderer);

    }

}
void destroy_ball(SDL_Renderer * m_renderer,double enteghali,double x[10],double y[13],int list_toop[13][10],int i_old, int j_old , int i , int j , int coll, vector<int> & bonus ,  balls_with_num ballsWithNum,vector<int> & lock,int find,vector<Mix_Chunk *> song , double &time_effect,vector<ImagePair> images) {
    if (list_toop[i][j - 1] != 0 && (i) < 13 && (i) >= 1 && (j - 1) >= 0 && (j - 1) < 10) {
        if (i == i_old && j - 1 == j_old) {}
        else {
            for (int o = 0; o < 6; o++) {
                if (list_toop[i][j - 1] == ballsWithNum.ball[coll][o]) {
                    find = 1;
                    bonus.push_back(10);
                    list_toop[i][j] = 0;
//                    ball_happy(m_renderer,x[j],y[i]+enteghali,900,images);
//                    SDL_RenderPresent(m_renderer);
//                    SDL_Delay(100);
                    destroy_ball(m_renderer,enteghali,x,y,list_toop, i, j, i, j - 1, coll, bonus, ballsWithNum, lock, find,song,time_effect,images);
                    if (o == 5) {
                        vector<int> a = {coll, i, j - 1};
                        lock.insert(lock.end(), a.begin(), a.end());
                    }

                }
            }
        }
    }
    if (list_toop[i][j + 1] != 0 && (i) < 13 && (i) >= 1 && (j + 1) >= 0 && (j + 1) < 10) {
        if (i == i_old && j + 1 == j_old) {}
        else {
            for (int o = 0; o < 6; o++) {
                if (list_toop[i][j + 1] == ballsWithNum.ball[coll][o]) {
                    find = 1;
                    bonus.push_back(10);
                    list_toop[i][j] = 0;
//                    ball_happy(m_renderer,x[j],y[i]+enteghali,900,images);
//                    SDL_RenderPresent(m_renderer);
//                    SDL_Delay(100);
                    destroy_ball(m_renderer,enteghali,x,y,list_toop, i, j, i, j + 1, coll, bonus, ballsWithNum, lock, find,song,time_effect,images);
                    if (o == 5) {
                        vector<int> a = {coll, i, j + 1};
                        lock.insert(lock.end(), a.begin(), a.end());
                    }
                }
            }
        }


    }
    if (list_toop[i - 1][j - 1] != 0 && (i - 1) < 13 && (i - 1) >= 1 && (j - 1) >= 0 && (j - 1) < 10) {
        if (i - 1 == i_old && j - 1 == j_old) {}
        else {
            for (int o = 0; o < 6; o++) {
                if (list_toop[i - 1][j - 1] == ballsWithNum.ball[coll][o]) {
                    find = 1;
                    bonus.push_back(10);
                    list_toop[i][j] = 0;
//                    ball_happy(m_renderer,x[j],y[i]+enteghali,900,images);
//                    SDL_RenderPresent(m_renderer);
//                    SDL_Delay(100);
                    destroy_ball(m_renderer,enteghali,x,y,list_toop, i, j, i - 1, j - 1, coll, bonus, ballsWithNum, lock, find,song,time_effect,images);
                    if (o == 5) {
                        vector<int> a = {coll, i-1, j - 1};
                        lock.insert(lock.end(), a.begin(), a.end());
                    }

                }
            }
        }
    }
    if (list_toop[i - 1][j] != 0 && (i - 1) < 13 && (i - 1) >= 1 && (j) >= 0 && (j) < 10) {
        if (i - 1 == i_old && j == j_old) {}
        else {
            for (int o = 0; o < 6; o++) {
                if (list_toop[i - 1][j] == ballsWithNum.ball[coll][o]) {
                    find = 1;
                    bonus.push_back(10);
                    list_toop[i][j] = 0;
//                    ball_happy(m_renderer,x[j],y[i]+enteghali,900,images);
//                    SDL_RenderPresent(m_renderer);
//                    SDL_Delay(100);
                    destroy_ball(m_renderer,enteghali,x,y,list_toop, i, j, i - 1, j, coll, bonus, ballsWithNum, lock, find,song,time_effect,images);
                    if (o == 5) {
                        vector<int> a = {coll, i - 1, j};
                        lock.insert(lock.end(), a.begin(), a.end());
                    }

                }
            }
        }

    }
    if (list_toop[i - 1][j+1] != 0 && (i - 1) < 13 && (i - 1) >= 1 && (j+1) >= 0 && (j+1) < 10) {
        if (i - 1 == i_old && j+1 == j_old) {}
        else {
            for (int o = 0; o < 6; o++) {
                if (list_toop[i - 1][j+1] == ballsWithNum.ball[coll][o]) {
                    find = 1;
                    bonus.push_back(10);
                    list_toop[i][j] = 0;
//                    ball_happy(m_renderer,x[j],y[i]+enteghali,900,images);
//                    SDL_RenderPresent(m_renderer);
//                    SDL_Delay(100);
                    destroy_ball(m_renderer,enteghali,x,y,list_toop, i, j, i - 1, j+1, coll, bonus, ballsWithNum, lock, find,song,time_effect,images);
                    if (o == 5) {
                        vector<int> a = {coll, i - 1, j+1};
                        lock.insert(lock.end(), a.begin(), a.end());
                    }

                }
            }
        }

    }
    if (list_toop[i + 1][j + 1] != 0 && (i + 1) < 13 && (i + 1) >= 1 && (j + 1) >= 0 && (j + 1) < 10) {
        if (i + 1 == i_old && j + 1 == j_old) {}
        else {
            for (int o = 0; o < 6; o++) {
                if (list_toop[i + 1][j + 1] == ballsWithNum.ball[coll][o]) {
                    find = 1;
                    bonus.push_back(10);
                    list_toop[i][j] = 0;
//                    ball_happy(m_renderer,x[j],y[i]+enteghali,900,images);
//                    SDL_RenderPresent(m_renderer);
//                    SDL_Delay(100);
                    destroy_ball(m_renderer,enteghali,x,y,list_toop, i, j, i + 1, j + 1, coll, bonus, ballsWithNum, lock, find,song,time_effect,images);
                    if (o == 5) {
                        vector<int> a = {coll, i+1, j + 1};
                        lock.insert(lock.end(), a.begin(), a.end());
                    }

                }
            }
        }

    }
    if (list_toop[i + 1][j] != 0 && (i + 1) < 13 && (i + 1) >= 1 && (j) >= 0 && (j) < 10) {
        if (i + 1 == i_old && j == j_old) {}
        else {
            for (int o = 0; o < 6; o++) {
                if (list_toop[i + 1][j] == ballsWithNum.ball[coll][o]) {
                    find = 1;
                    bonus.push_back(10);
                    list_toop[i][j] = 0;
//                    ball_happy(m_renderer,x[j],y[i]+enteghali,900,images);
//                    SDL_RenderPresent(m_renderer);
//                    SDL_Delay(100);
                    destroy_ball(m_renderer,enteghali,x,y,list_toop, i, j, i + 1, j, coll, bonus, ballsWithNum, lock, find,song,time_effect,images);
                    if (o == 5) {
                        vector<int> a = {coll, i+1, j};
                        lock.insert(lock.end(), a.begin(), a.end());
                    }

                }
            }
        }

    }
    if (list_toop[i + 1][j-1] != 0 && (i + 1) < 13 && (i + 1) >= 1 && (j-1) >= 0 && (j-1) < 10) {
        if (i + 1 == i_old && j-1 == j_old) {}
        else {
            for (int o = 0; o < 6; o++) {
                if (list_toop[i + 1][j-1] == ballsWithNum.ball[coll][o]) {
                    find = 1;
                    bonus.push_back(10);
                    list_toop[i][j] = 0;
//                    ball_happy(m_renderer,x[j],y[i]+enteghali,900,images);
//                    SDL_RenderPresent(m_renderer);
//                    SDL_Delay(100);
                    destroy_ball(m_renderer,enteghali,x,y,list_toop, i, j, i + 1, j-1, coll, bonus, ballsWithNum, lock, find,song,time_effect,images);
                    if (o == 5) {
                        vector<int> a = {coll, i+1, j-1};
                        lock.insert(lock.end(), a.begin(), a.end());
                    }

                }
            }
        }

    }
    if (find == 1) {
        ball_happy(m_renderer,x[j],y[i]+enteghali,900,images);
        SDL_RenderPresent(m_renderer);
        int channel = Mix_PlayChannel(-1,song[1], 0);;
        SDL_Delay(100);
        time_effect=-1;
//        bonus.push_back(10);
        list_toop[i][j] = 0;
    }
    if (find==0)
        list_toop[i][j]=coll;
}
void back_lock(int list_toop [13][10],vector<int> &lock, balls_with_num ballsWithNum){
    int a = lock.size();
    for(int o = 0 ; o<(a/3) ; o++) {
        int col=lock[o*3] ;
        int i = lock[o*3+1];
        int j = lock[o*3+2];
        list_toop[i][j]=col;
    }
    lock.clear();
}
void d_ball(int list_toop[13][10],int i_old, int j_old , int i , int j , vector<int> & bonus,vector<int> & animation ) {
    if (list_toop[i][j - 1] > 0 && list_toop[i][j - 1]<=21 && (i) < 13 && (i) >= 2 && (j - 1) >= 0 && (j - 1) < 10) {
        if (i == i_old && j - 1 == j_old) {}
        else {
            bonus.push_back(20);
            animation.push_back(i);
            animation.push_back(j);
            animation.push_back(list_toop[i][j]);
            list_toop[i][j] = 43;
            d_ball(list_toop, i, j, i, j - 1, bonus,animation);
        }
    }
    if (list_toop[i][j + 1] > 0 &&list_toop[i][j + 1] <=21 && (i) < 13 && (i) >= 2 && (j + 1) >= 0 && (j + 1) < 10) {
        if (i == i_old && j + 1 == j_old) {}
        else {
            bonus.push_back(20);
            animation.push_back(i);
            animation.push_back(j);
            animation.push_back(list_toop[i][j]);
            list_toop[i][j] = 43;
            d_ball(list_toop, i, j, i, j + 1,  bonus,animation);
        }
    }
    if (list_toop[i - 1][j - 1] > 0 && list_toop[i - 1][j - 1]<=21 && (i - 1) < 13 && (i - 1) >= 2 && (j - 1) >= 0 && (j - 1) < 10) {
        if (i - 1 == i_old && j - 1 == j_old) {}
        else {
            for (int o = 0; o < 6; o++) {
                bonus.push_back(20);
                animation.push_back(i);
                animation.push_back(j);
                animation.push_back(list_toop[i][j]);
                list_toop[i][j] = 43;
                d_ball(list_toop, i, j, i - 1, j - 1,  bonus,animation);
            }
        }
    }
    if (list_toop[i - 1][j] > 0&& list_toop[i - 1][j]<=21 && (i - 1) < 13 && (i - 1) >= 2 && (j) >= 0 && (j) < 10) {
        if (i - 1 == i_old && j == j_old) {}
        else {
            bonus.push_back(20);
            animation.push_back(i);
            animation.push_back(j);
            animation.push_back(list_toop[i][j]);
            list_toop[i][j] = 43;
            d_ball(list_toop, i, j, i - 1, j, bonus,animation);
        }
    }
    if (list_toop[i - 1][j+1] > 0 && list_toop[i - 1][j+1]<=21 && (i - 1) < 13 && (i - 1) >= 2 && (j+1) >= 0 && (j+1) < 10) {
        if (i - 1 == i_old && j+1 == j_old) {}
        else {
            bonus.push_back(20);
            animation.push_back(i);
            animation.push_back(j);
            animation.push_back(list_toop[i][j]);
            list_toop[i][j] = 43;
            d_ball(list_toop, i, j, i - 1, j+1, bonus,animation);
        }

    }
    if (list_toop[i + 1][j + 1] > 0 &&list_toop[i + 1][j + 1]<=21 && (i + 1) < 13 && (i + 1) >= 2 && (j + 1) >= 0 && (j + 1) < 10) {
        if (i + 1 == i_old && j + 1 == j_old) {}
        else {
            bonus.push_back(20);
            animation.push_back(i);
            animation.push_back(j);
            animation.push_back(list_toop[i][j]);
            list_toop[i][j] = 43;
            d_ball(list_toop, i, j, i + 1, j + 1, bonus,animation);
        }

    }
    if (list_toop[i + 1][j] > 0 && list_toop[i + 1][j]<=21 &&(i + 1) < 13 && (i + 1) >= 2 && (j) >= 0 && (j) < 10) {
        if (i + 1 == i_old && j == j_old) {}
        else {
            bonus.push_back(20);
            animation.push_back(i);
            animation.push_back(j);
            animation.push_back(list_toop[i][j]);
            list_toop[i][j] = 43;
            d_ball(list_toop, i, j, i + 1, j, bonus,animation);

        }

    }
    if (list_toop[i + 1][j-1] > 0 && list_toop[i + 1][j-1]<=21  && (i + 1) < 13 && (i + 1) >= 2 && (j-1) >= 0 && (j-1) < 10) {
        if (i + 1 == i_old && j-1 == j_old) {}
        else {
            bonus.push_back(20);
            animation.push_back(i);
            animation.push_back(j);
            animation.push_back(list_toop[i][j]);
            list_toop[i][j] = 43;
            d_ball(list_toop, i, j, i + 1, j-1, bonus,animation);
        }

    }
    animation.push_back(i);
    animation.push_back(j);
    animation.push_back(list_toop[i][j]);
    list_toop[i][j] = 43 ;
}
void g_ball(int list_toop[13][10],int i_0 , int j_0 ,int i_old , int j_old ,int i , int j, vector<int>bonus,vector<Mix_Chunk *>song  , vector<int> & animation){

    if (list_toop[i][j + 1] == 0 && (i) < 13 && (i) >= 2 && (j + 1) >= 0 && (j + 1) < 10){
        list_toop[i][j+1]=43;
        g_ball(list_toop,i_0,j_0,i,j,i,j+1,bonus,song,animation);

    }
    if (list_toop[i + 1][j] == 0 && (i + 1) < 13 && (i + 1) >= 2 && (j) >= 0 && (j) < 10){
        list_toop[i+1][j]=43;
        g_ball(list_toop,i_0,j_0,i,j,i+1,j,bonus,song,animation);

    }
    if (list_toop[i - 1][j] == 0 && (i - 1) >= i_0 && (i - 1) >= 2 && (j) >= 0 && (j) < 10){
        list_toop[i-1][j]=43 ;
        g_ball(list_toop,i_0,j_0,i,j,i-1,j,bonus,song,animation);

    }
    if (list_toop[i][j - 1] == 0 && (i) < 13 && (i) >= 2 && (j - 1) >= 0 && (j - 1) < 10){
        list_toop[i][j-1]=43 ;
        g_ball(list_toop,i_0,j_0,i,j,i,j-1,bonus,song,animation);
    }

    //***************************************
    if (list_toop[i][j - 1] == 37 && (i) < 13 && (i) >= 2 && (j - 1) >= 0 && (j - 1) < 10) {
        if (i == i_old && j - 1 == j_old) {}
        else {
            int channel = Mix_PlayChannel(-1,song[1], 0);;
            animation.push_back(i_0+1);
            animation.push_back(j_0);
            animation.push_back(list_toop[i_0][j_0]);
            list_toop[i_0][j_0] = 43;
            d_ball(list_toop, i_0 + 1, j_0, i_0 + 1, j_0, bonus,animation);
            return;
        }
    }
    if (list_toop[i][j + 1] == 37 && (i) < 13 && (i) >= 2 && (j + 1) >= 0 && (j + 1) < 10) {
        if (i == i_old && j + 1 == j_old) {}
        else {
            int channel = Mix_PlayChannel(-1,song[1], 0);;
            animation.push_back(i_0+1);
            animation.push_back(j_0);
            animation.push_back(list_toop[i_0][j_0]);
            list_toop[i_0][j_0] = 43;
            d_ball(list_toop, i_0 + 1, j_0, i_0 + 1, j_0, bonus,animation);
            return;
        }
    }
    if (list_toop[i - 1][j] == 37 && (i - 1) <= i_0 && (i - 1) >= 2 && (j) >= 0 && (j) < 10) {
        if (i - 1 == i_old && j == j_old) {}
        else {
            int channel = Mix_PlayChannel(-1,song[1], 0);;
            animation.push_back(i_0+1);
            animation.push_back(j_0);
            animation.push_back(list_toop[i_0][j_0]);
            list_toop[i_0][j_0] = 43;
            d_ball(list_toop, i_0 + 1, j_0, i_0 + 1, j_0, bonus,animation);
            return;
        }
    }
    if (list_toop[i + 1][j] == 37 && (i + 1) < 13 && (i + 1) >= 2 && (j) >= 0 && (j) < 10) {
        if (i + 1 == i_old && j == j_old) {}
        else {
            int channel = Mix_PlayChannel(-1,song[1], 0);;
            animation.push_back(i_0+1);
            animation.push_back(j_0);
            animation.push_back(list_toop[i_0][j_0]);
            list_toop[i_0][j_0] = 43;
            d_ball(list_toop, i_0 + 1, j_0, i_0 + 1, j_0, bonus,animation);
            return;
        }
    }


}
void sort_list( vector<string> & mode , string name , int point) {
    vector<int>list;
    string a;
    string c = name+'+'+to_string(point);
    int b;
    for(int i =0 ; i<mode.size() && i<20 ;i++){
        for(int j = 0 ; j<mode[i].length();j++) {
            if (mode[i][j]=='+'){
                a=mode[i].substr(j+1,mode[i].length()-(j+1));
                b = stoi(a);
                list.push_back(b);
            }
        }

    }
    if(point<list[list.size()-1]){
        mode.push_back(c);
    }
    else if(point>list[0]) {
        mode.insert(mode.begin(), c);
    }
    else {
        for (int i = 0; i < list.size() && i < 20; i++) {
            if (point <= list[i] && point > list[i + 1]) {
                mode.insert(mode.begin() + i+1, c);
            }
        }
    }
}
void check_ball(int listtoop[13][10],int x_y_array[2] , double x_, double y_, double x[10],double y[13],int width){
    int y_arr = x_y_array[0];
    int x_arr = x_y_array[1];
    double x_center = x[x_arr];
    double y_center = y[y_arr];
    if(x_==x_center){
        x_y_array[0]+=1;
    }
    else {
        double zavieh = (y_-y_center)/(x_-x_center) ;
        if(zavieh>2.41 || zavieh<-2.41) {
            if (y_ < y_center) {
                if (listtoop[y_arr + 1][x_arr] == 0)
                    x_y_array[0] += 1;
                else if (x_ > x_center) {
                    if (listtoop[y_arr + 1][x_arr + 1] == 0) {
                        x_y_array[0] += 1;
                        x_y_array[1] += 1;
                    } else if (listtoop[y_arr][x_arr + 1] == 0)
                        x_y_array[1] += 1;
                }
                else {
                    if (listtoop[y_arr + 1][x_arr - 1] == 0) {
                        x_y_array[0] += 1;
                        x_y_array[1] -= 1;
                    } else if (listtoop[y_arr][x_arr - 1] == 0)
                        x_y_array[1] -= 1;
                }
            }
            else {
                if(listtoop[y_arr+1][x_arr]==0) {
                    x_y_array[0] += 1;
                }
                else if(x_>x_center){
                    if(listtoop[y_arr+1][x_arr+1]==0){
                        x_y_array[0]+=1;
                        x_y_array[1]+=1;
                    }
                    else if(listtoop[y_arr][x_arr+1]==0){
                        x_y_array[1]+=1;
                    }
                }
                else{
                    if(listtoop[y_arr+1][x_arr-1]==0){
                        x_y_array[0]+=1;
                        x_y_array[1]-=1;

                    }
                    else if(listtoop[y_arr][x_arr-1]==0) {
                        x_y_array[1]-=1;
                    }
                }
            }
        }
        else if(zavieh>.41 || zavieh<.41){
            if(y_<y_center) {
                if(x_<x_center){
                    if(listtoop[y_arr-1][x_arr-1]==0) {
                        x_y_array[0] -= 1;
                        x_y_array[1] -= 1;
                    }
                    else if(listtoop[y_arr-1][x_arr]==0){
                        x_y_array[0]-=1;
                    }
                    else if (listtoop[y_arr][x_arr-1]==0){
                        x_y_array[1]-=1;
                    }
                }
                else{
                    if(listtoop[y_arr-1][x_arr+1]==0) {
                        x_y_array[0]-=1;
                        x_y_array[1]+=1;
                    }
                    else if(listtoop[y_arr-1][x_arr]==0){
                        x_y_array[0]-=1;
                    }
                    else if(listtoop[y_arr][x_arr+1]==0){
                        x_y_array[1]+=1;
                    }
                }
            }
            else{
                if(x_>x_center) {
                    if(x_arr<9 && listtoop[y_arr][x_arr+1]==0){
                        x_y_array[1]+=1;
                    }
                    else if (x_arr < 9 && listtoop[y_arr+1][x_arr+1]==0) {
                        x_y_array[0] += 1;
                        x_y_array[1]+=1;
                    }
                    else if(x_arr<9 && listtoop[y_arr+1][x_arr]==0){
                        x_y_array[0]+=1;
                    }
                    else if (x_arr==9){
                        x_y_array[0]+=1;
                    }
                }
                else {
                    if(x_arr>0 && listtoop[y_arr][x_arr-1]==0){
                        x_y_array[1]-=1;
                    }
                    else if (x_arr > 0 && listtoop[y_arr+1][x_arr-1]==0) {
                        x_y_array[0] += 1;
                        x_y_array[1]-=1;
                    }
                    else if(x_arr>0 && listtoop[y_arr+1][x_arr]==0){
                        x_y_array[0]+=1;
                    }
                    else if(x_arr==0){
                        x_y_array[0]+=1;
                    }
                }
            }

        }
        else {
            if (x_ > x_center) {
                x_y_array[1] += 1;
            }
            else {
                x_y_array[1] -= 1;
            }
        }
    }
}
//************