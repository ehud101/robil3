#include "heightmap.h"
#include "rdbg.h"
#include <cstdio>
#include <ros/ros.h>


using namespace cv;
#define OBSTACLE_THRESH 0.4
#define HEIGHT_UNKNOWN -100.0



HeightMap::HeightMap(int width, int height, per::configConfig *p=NULL)
{
    _dynamic = p;
    _heights.resize(width*height, HEIGHT_UNKNOWN);
    _types.resize(width*height, TYPE_UNSCANNED);
    _features.resize(width*height, FEATURE_UNKNOWN);
    _width = width;
    _height = height;
    _min = -3;
    _max = 3;
    _compass = imread("compass.png");
    _arrow = imread("arrow.png");
    _refPoint = Vec2D(0,0);
}

HeightMap::~HeightMap()
{
    _heights.clear();
}

double& HeightMap::_at(int x, int y)
{
    //printf("%d\n", y*_width+x);
    return _heights[y*_width+x];
}

int& HeightMap::_typeAt(int x, int y)
{
    return _types[y*_width+x];
}

int& HeightMap::_featureAt(int x, int y)
{
    return _features[y*_width+x];
}
void HeightMap::setRelativeHeightAt(int x, int y, double height)
{

    if(x >= _width/2) { shiftRight(); return; }
    else if(x <= -_width/2) { shiftLeft(); return; }
    
    if(y >= _height/2) { shiftUp(); return; }
    else if(y <= -_height/2) {  shiftDown(); return; }
    
    x = _width/2 - x;
    y = _height/2 - y;
    
    if(_at(x,y) < _min) _at(x,y) = height;
    else _at(x,y) = _at(x,y)*0.9 + height*0.1;
}

void HeightMap::setRelativeTypeAt(int x, int y, int type)
{

    if(x >= _width/2) { shiftRight(); return; }
    else if(x <= -_width/2) { shiftLeft(); return; }
    
    if(y >= _height/2) { shiftUp(); return; }
    else if(y <= -_height/2) {  shiftDown(); return; }
    
    x = _width/2 - x;
    y = _height/2 - y;
    
    _typeAt(x,y) = type;
}

void HeightMap::setRelativeFeatureAt(int x, int y, int feature)
{

    if(x >= _width/2) { shiftRight(); return; }
    else if(x <= -_width/2) { shiftLeft(); return; }
    
    if(y >= _height/2) { shiftUp(); return; }
    else if(y <= -_height/2) {  shiftDown(); return; }
    
    x = _width/2 - x;
    y = _height/2 - y;
    
    _featureAt(x,y) = feature;
}

void HeightMap::setAbsoluteHeightAt(int x, int y, double height)
{
    x -= _refPoint.x;
    y -= _refPoint.y;
    if(height < HEIGHT_UNKNOWN+5) return;
    //if(height < _min) _min = height;
    //if(height > _max) _max = height;
    setRelativeHeightAt(x,y,height);
}

void HeightMap::shiftLeft()
{
    _refPoint = _refPoint.add(Vec2D(-_width/2, 0));
    for(int y = -_height/2+1; y <= _height/2-1; y++)
        for(int x = _width/2-1; x >= -_width/2+1; x--)
        {
            double h = getRelativeHeightAt(x-_width/2, y);
            int t = getRelativeTypeAt(x-_width/2, y);
            int f = getRelativeFeatureAt(x-_width/2, y);
            double x1 = _width/2 - x;
            double y1 = _height/2 - y;
            _at(x1,y1) = h;
            _featureAt(x1,y1) = f;
            _typeAt(x1,y1) = t;
        }
    //rdbg("left");
}

void HeightMap::shiftRight()
{
    _refPoint = _refPoint.add(Vec2D(_width/2, 0));
    for(int y = -_height/2+1; y <= _height/2-1; y++)
        for(int x = -_width/2+1; x <= _width/2-1; x++)
        {
            double h = getRelativeHeightAt(x+_width/2, y);
            int t = getRelativeTypeAt(x+_width/2, y);
            int f = getRelativeFeatureAt(x+_width/2, y);
            double x1 = _width/2 - x;
            double y1 = _height/2 - y;
            _at(x1,y1) = h;
            _featureAt(x1,y1) = f;
            _typeAt(x1,y1) = t;
        }
    //rdbg("left");

}
void HeightMap::shiftUp()
{
    _refPoint = _refPoint.add(Vec2D(0, _height/2));
    for(int y = -_height/2+1; y <= _height/2-1; y++)
        for(int x = _width/2-1; x >= -_width/2+1; x--)
        {
            double h = getRelativeHeightAt(x, y+_height/2);
            int t = getRelativeTypeAt(x, y+_height/2);
            int f = getRelativeFeatureAt(x, y+_height/2);
            double x1 = _width/2 - x;
            double y1 = _height/2 - y;
            _at(x1,y1) = h;
            _featureAt(x1,y1) = f;
            _typeAt(x1,y1) = t;
        }
    //rdbg("up");
}

void HeightMap::shiftDown()
{
    _refPoint = _refPoint.add(Vec2D(0, -_height/2));
    for(int y = _height/2-1; y >= -_height/2+1; y--)
        for(int x = _width/2-1; x >= -_width/2+1; x--)
        {
            double h = getRelativeHeightAt(x, y-_height/2);
            int t = getRelativeTypeAt(x, y-_height/2);
            int f = getRelativeFeatureAt(x, y-_height/2);
            double x1 = _width/2 - x;
            double y1 = _height/2 - y;
            _at(x1,y1) = h;
            _featureAt(x1,y1) = f;
            _typeAt(x1,y1) = t;
        }
    //rdbg("down");
}

double HeightMap::getRelativeHeightAt(int x, int y)
{
    if(x >= _width/2 || x <= -_width/2) return HEIGHT_UNKNOWN;
    if(y >= _height/2 || y <= -_height/2) return HEIGHT_UNKNOWN;
    x = _width/2 - x;
    y = _height/2 - y;
    return _at(x,y);
}

double HeightMap::getAbsoluteHeightAt(int x, int y)
{
    x -= _refPoint.x;
    y -= _refPoint.y;
    return getRelativeHeightAt(x,y);
}

int HeightMap::getRelativeTypeAt(int x, int y)
{
    if(x >= _width/2 || x <= -_width/2) return TYPE_UNSCANNED;
    if(y >= _height/2 || y <= -_height/2) return TYPE_UNSCANNED;
    x = _width/2 - x;
    y = _height/2 - y;
    return _typeAt(x,y);
}

int HeightMap::getRelativeFeatureAt(int x, int y)
{
    if(x >= _width/2 || x <= -_width/2) return FEATURE_UNKNOWN;
    if(y >= _height/2 || y <= -_height/2) return FEATURE_UNKNOWN;
    x = _width/2 - x;
    y = _height/2 - y;
    return _featureAt(x,y);
}
void HeightMap::displayConsole()
{
    for(int y = 0; y < _height; y++)
    {
        for(int x = 0; x < _width; x++)
        {
            printf("%3.3f\t", this->_at(x,y));
        }
        printf("\n");
    }
}
int showX = -1, showY = -1;
int test_x = -1, test_y = -1;


Mat HeightMap::add_arrow(Mat image, int rotation, int px, int py, int enlarger)
{
  Mat arrow;
  cv::Point2f pt(_arrow.rows/2, _arrow.cols/2);
  cv::Mat r = cv::getRotationMatrix2D(pt, 90+rotation, 1.0);
  cv::warpAffine(_arrow, arrow, r, cv::Size(_arrow.rows, _arrow.rows));
  px *= 5;
  py *= 5; //transformation to 20x20cm cell coords
  px -= _refPoint.x;
  py -= _refPoint.y;
  if(px >= _width/2 || px <= -_width/2 || py >= _height/2 || py <= -_height/2)
  {
      return image;
  }
  px = _width/2 - px;
  py = _height/2 - py;
  for(int i = 0; i < _arrow.rows; i++)
      for(int j = 0; j < _arrow.cols; j++)
          if(arrow.at<Vec3b>(i,j) != Vec3b(0,0,0))
              image.at<Vec3b>(i+px*enlarger-arrow.rows/2, j+py*enlarger-arrow.cols/2) = arrow.at<Vec3b>(i, j);
  return image;
}

void onMouseClick2(int event, int x, int y, int flags, void *param)
{

    Mat *img = ((Mat *)param);
    if (event == CV_EVENT_LBUTTONDOWN)
    {
        cout << "x: " << x << " y: " << y << "\t" << img->size() <<endl;
        test_x = showX = y;
        test_y = showY = x;
    }
}

void HeightMap::displayGUI(int rotation, int px, int py, int enlarger)
{
    // rdbg("gui enter");
    Mat image = this->generateMat(rotation, px, py, enlarger);
    //put the tempory arrow representing my position and rotation on the map
    image = add_arrow(image, rotation, px, py, enlarger);
    char name[30];
    sprintf(name, "GUI %d", _width);

    if (!image.empty())
    {
        setMouseCallback(name, onMouseClick2, &image);
        imshow(name, image);
        waitKey(100);
    }

}
void onMouseClick(int event, int x, int y, int flags, void *param)
{

    Mat *img = ((Mat *)param);

    if (event == CV_EVENT_LBUTTONDOWN)
    {
//        cout << "x: " << x << " y: " << y << "\t" << img->size() <<endl;
        test_x = showX = y;
        test_y = showY = x;
    }
}
Mat HeightMap::generateMat(int rotation, int px, int py, int enlarger)
{
    Mat image(_width*enlarger, _height*enlarger, CV_8UC3);
    cvtColor(image, image, CV_BGR2HSV);

    for(int y = 0; y < _height*enlarger; y++)
        for(int x = 0; x < _width*enlarger; x++)
        {
            double h = this->_at(x/enlarger,y/enlarger);
            if (showX == x && showY == y)
            {
                cout << "x: " << x << " y: " << y << "\t" << h << endl;
                showX = showY = -1;

            }
            if(h <= _min)
            {
                image.at<Vec3b>(x,y) = Vec3b(0,0,100);
                continue;
            }
            double c = (h - _min)/(_max-_min);
            image.at<Vec3b>(x,y) = Vec3b(120*(1-c),240, 240);
        }
    cvtColor(image, image, CV_HSV2BGR);
    return image;
}
Mat HeightMap::generateMat(int enlarger)
{
    Mat image(_width*enlarger, _height*enlarger, CV_8UC3);
    //cvtColor(image, image, CV_BGR2HSV);

    for(int y = 0; y < _height*enlarger; y++)
    {
        for(int x = 0; x < _width*enlarger; x++)
        {
            int t = this->_types[x/enlarger + _width*(y/enlarger)];

            if(t == TYPE_CLEAR) image.at<Vec3b>(x,y) = Vec3b(255,255,255);
            else if(t == TYPE_OBSTACLE) image.at<Vec3b>(x,y) = Vec3b(255,0,0);
            else if(t == TYPE_UNSCANNED) image.at<Vec3b>(x,y) = Vec3b(60,160,60);

            int f = this->_features[x/enlarger + _width*(y/enlarger)];

            if(f == FEATURE_ROAD)
            {
                image.at<Vec3b>(x,y) = Vec3b(100,100,100);
            }
            if(f == FEATURE_NOT_ROAD)
            {
                image.at<Vec3b>(x,y) = Vec3b(60,100,150);
            }
        }
    }
    //cvtColor(image, image, CV_HSV2BGR);
    int px = _width/2+25;
    int py = _height/2;
    Mat arrow;
    cv::Point2f pt(_arrow.rows/2, _arrow.cols/2);
    cv::Mat r = cv::getRotationMatrix2D(pt, 90, 1.0);
    cv::warpAffine(_arrow, arrow, r, cv::Size(_arrow.rows, _arrow.rows));
    for(int i = 0; i < _arrow.rows; i++)
    {
        for(int j = 0; j < _arrow.cols; j++)
        {
            if(arrow.at<Vec3b>(i,j) != Vec3b(0,0,0))
            {
                image.at<Vec3b>(i+px*enlarger-arrow.rows/2, j+py*enlarger-arrow.cols/2) = arrow.at<Vec3b>(i, j);
            }
        }
    }
    return image;
}

void HeightMap::displayTypesGUI(Mat lanes,int enlarger)
{
    //int enlarger = 3;
    Mat image = generateMat(enlarger);
    if (image.empty())
        return;
    setMouseCallback("TerrainTypeUI", onMouseClick, &image);
    imshow("TerrainTypeUI", image);
    
    cv::waitKey(200);
}
int lowThreshold = 24;
int morph_elem = 0;
int morph_size = 10;
int morph_operator = 0;
int const max_operator = 4;
int const max_elem = 2;
int const max_kernel_size = 21;
int erode_size = 2;

void Morphology_Operations( int, void* )
{
}

std::vector<int> getConvolution(string str, int size)
{
    std::vector<int> vect, conv;

    std::stringstream ss(str);

    int i;

    while (ss >> i)
    {
        vect.push_back(i);

        if (ss.peek() == ',')
            ss.ignore();
    }
    if (!size%2)
        size--;
    if (vect.size() != size)
        vect.assign(size, 1);
    conv.assign(size*size, 1);
    int mid = vect.size() / 2;
    for (int i = 0; i < vect.size(); i++)
    {
        for (int j = 0; j < vect.size(); j++)
        {
            if (i > mid)
            {
                if (i > j && j > vect.size() - i - 1)
                    conv.at(i * vect.size() + j) = vect.at(i);
                else
                    conv.at(i * vect.size() + j) = vect.at(j);
            }
            else if (i < mid)
            {
                if (i < j && j < vect.size() - i - 1)
                    conv.at(i * vect.size() + j) = vect.at(i);
                else
                    conv.at(i * vect.size() + j) = vect.at(j);
            }
            else
                conv.at(i * vect.size() + j) = vect.at(j);
        }

    }

    return conv;
}

double HeightMap::calc_height(int x, int y, std::vector<int> conv)
{
    if (_at(x, y) == HEIGHT_UNKNOWN)
        return HEIGHT_UNKNOWN;
    double height = 0;
    double counter = 0;
    int radius = (int)sqrt(conv.size());
    int k = 0;
    for (int i = x - radius / 2; i <= x + radius / 2; i++)
        for (int j = y - radius / 2; j <= y + radius / 2; j++)
        {
            double mul = conv.at(k++);
            if (i < 0 || i > _width || j < 0 || j > _height || _at(i, j) == HEIGHT_UNKNOWN)
                return 0.0;
            counter += abs(mul);
            height += mul * _at(i, j);
        }
    if (test_y == y && test_x == x)
    {
        cout << counter << ", " << height << " = " << height / counter << endl;
        test_x = -1, test_y = -1;
    }
//    if (_at(x, y) > 0.4)
//        cout << counter << ", " << height << " = " << height / counter << endl;
    if (counter)
      height /= (1.0 * counter);

    return height;
}

double HeightMap::calc_slope(int x, int y, std::vector<int> conv)
{
    if (_at(x, y) == HEIGHT_UNKNOWN)
        return HEIGHT_UNKNOWN;
    double height = 0;
    double counter = 0;
    int radius = (int)sqrt(conv.size());
    int k = 0;
    for (int i = x - radius; i <= x + radius; i++)
        for (int j = y - radius; j <= y + radius; j++)
        {
            double mul = conv.at(k++);
            if (i < 0 || i > _width || j < 0 || j > _height || _at(i, j) == HEIGHT_UNKNOWN)
                continue;
            counter += abs(mul);
            height += mul * _at(i, j);
        }
    if (test_y == y && test_x == x)
    {
        cout << counter << ", " << height << " = " << height / counter << endl;
    }
    height /= counter;
    return height;
}

double HeightMap::getHeightAt(int x, int y)
{

}

void HeightMap::calculateTypes()//Vec3D position, Rotation myRot)
{
    int mul;
    std::vector<int> conv = getConvolution(_dynamic->convolution_type, _dynamic->convolution_size);
    int conv_x[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    std::vector<int> slope_conv_x; slope_conv_x.assign(conv_x, conv_x+9);
    int conv_y[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    std::vector<int> slope_conv_y; slope_conv_y.assign(conv_y, conv_y+9);
    const int road_thresh = 5;
    for(int i = 1; i < _width-1; i++)
    {
        for(int j = 1; j < _height-1; j++)
        {
            double height = calc_height(i,j,conv);
            if (height > _dynamic->obstacle_threshold)
            {
                double gx = calc_height(i, j, slope_conv_x);
                double gy = calc_height(i, j, slope_conv_y);
                if (sqrt(gx * gx + gy * gy) > _dynamic->slope_threshold)
                  {
                    _types[j*_width+i] = TYPE_OBSTACLE;
//                    std::cout << i << ", " << j << ": " << gx << ", " << gy << std::endl;
                  }
                else
                    _types[j*_width+i] = TYPE_CLEAR;
            }
            else if(height == HEIGHT_UNKNOWN)
                _types[j*_width+i] = TYPE_UNSCANNED;
            else
                _types[j*_width+i] = TYPE_CLEAR;

        }
    }
}

HeightMap HeightMap::deriveMap(int px, int py, Rotation r)
{
    //according to ROBIL map specs
    px*=5;
    py*=5; //transformation from real-world coords [m] to 20x20cm cell coords
    px -= _refPoint.x;
    py -= _refPoint.y;
    HeightMap ans(150, 150);
    Quaternion q = GetFromRPY(r);
    Vec3D right3 = GetRightVector(q.x,q.y,q.z,q.w);
    Vec3D front3 = GetFrontVector(q.x,q.y,q.z,q.w);
    Vec2D front(front3.x, front3.y);
    Vec2D right(right3.x, right3.y);
    front = front.normalize();
    right = right.normalize();
    Vec2D pos(px,py);
    for(int i = -74; i < 74; i++)
        for(int j = -74; j < 74; j++)
        {
            Vec2D pt = pos.add(front.multiply(-j+25)).add(right.multiply(i));
            ans.setRelativeHeightAt(-j,i, getRelativeHeightAt(pt.x, pt.y));
            ans.setRelativeTypeAt(-j,i, getRelativeTypeAt(pt.x, pt.y));
            ans.setRelativeFeatureAt(-j,i, getRelativeFeatureAt(pt.x, pt.y));
        }
    return ans;
}

HeightMap HeightMap::deriveMiniMap(int px, int py, Rotation r)
{
    //according to ROBIL map specs
    px*=5;
    py*=5; //transformation from real-world coords [m] to 20x20cm cell coords
    px -= _refPoint.x;
    py -= _refPoint.y;
    HeightMap ans(50, 30);
    Quaternion q = GetFromRPY(r);
    Vec3D right3 = GetRightVector(q.x,q.y,q.z,q.w);
    Vec3D front3 = GetFrontVector(q.x,q.y,q.z,q.w);
    Vec2D front(front3.x, front3.y);
    Vec2D right(right3.x, right3.y);
    front = front.normalize();
    right = right.normalize();
    Vec2D pos(px,py);
    for(int i = -14; i < 14; i++)
        for(int j = -24; j < 24; j++)
        {
            Vec2D pt = pos.add(front.multiply(-j+25)).add(right.multiply(i));
            ans.setRelativeHeightAt(-j,i, getRelativeHeightAt(pt.x, pt.y));
            ans.setRelativeTypeAt(-j,i, getRelativeTypeAt(pt.x, pt.y));
            ans.setRelativeFeatureAt(-j,i, getRelativeFeatureAt(pt.x, pt.y));
        }
    return ans;
}


vector<double>& HeightMap::getHeights()
{
    return _heights;
}


vector<int>& HeightMap::getTypes()
{
    return _types;
}


vector<int>& HeightMap::getFeatures()
{
    return _features;
}

/** 
 * Walrus Experiment:
 */

int HeightMap::getAbsoluteFeatureAt(int x, int y)
{
    x -= _refPoint.x;
    y -= _refPoint.y;
    return getRelativeFeatureAt(x,y);
}

void HeightMap::setAbsoluteFeatureAt(int x, int y, int feature)
{
    x -= _refPoint.x;
    y -= _refPoint.y;
    //if(height < HEIGHT_UNKNOWN+5) return;
    //if(height < _min) _min = height;
    //if(height > _max) _max = height;
    setRelativeFeatureAt(x,y,feature);
}


int HeightMap::getAbsoluteTypeAt(int x, int y)
{

    x -= _refPoint.x;
    y -= _refPoint.y;
    //if(height < HEIGHT_UNKNOWN+5) return;
    //if(height < _min) _min = height;
    //if(height > _max) _max = height;
    getRelativeTypeAt(x,y);
}
