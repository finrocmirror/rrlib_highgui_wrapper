//
// You received this file as part of RRLib
// Robotics Research Library
//
// Copyright (C) Finroc GbR (finroc.org)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
//----------------------------------------------------------------------
/*!\file    tWindow.cpp
 *
 * \author  Tobias Foehst
 *
 * \date    2010-12-26
 *
 */
//----------------------------------------------------------------------
#include "rrlib/highgui_wrapper/tWindow.h"

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <highgui.h>

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Debugging
//----------------------------------------------------------------------
#include <cassert>

//----------------------------------------------------------------------
// Namespace usage
//----------------------------------------------------------------------
using namespace rrlib::highgui;

//----------------------------------------------------------------------
// Forward declarations / typedefs / enums
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Const values
//----------------------------------------------------------------------
const unsigned int cNUMBER_OF_COLORS = 13;
const struct
{
  unsigned char red;
  unsigned char green;
  unsigned char blue;
} cPREDEFINED_COLORS[cNUMBER_OF_COLORS] =
{
  {   0,   0,   0 }, // black
  { 255,   0,   0 }, // red
  {   0, 255,   0 }, // green
  {   0,   0, 255 }, // blue
  {   0, 255, 255 }, //
  { 255,   0, 255 }, //
  { 255, 255,   0 }, //
  { 127,   0,   0 }, // dark red
  {   0, 127,   0 }, // dark green
  {   0,   0, 127 }, // dark blue
  {   0, 127, 127 }, // dark
  { 127,   0, 127 }, // dark
  { 127, 127,   0 }  // dark
};

//----------------------------------------------------------------------
// Implementation
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// tWindow constructors
//----------------------------------------------------------------------
tWindow::tWindow(const std::string &name, unsigned int width, unsigned int height)
    : name(name),
    width(width),
    height(height),
    image(0),
    r(0), g(0), b(0)
{
  cvNamedWindow(this->name.c_str(), CV_WINDOW_AUTOSIZE);
  cvMoveWindow(this->name.c_str(), 0, 0);
  image = cvCreateImage(cvSize(this->width, this->height), IPL_DEPTH_8U, 3);
  this->Clear();
}

//----------------------------------------------------------------------
// tWindow destructor
//----------------------------------------------------------------------
tWindow::~tWindow()
{
  cvReleaseImage(&this->image);
  cvDestroyWindow(this->name.c_str());
}

//----------------------------------------------------------------------
// tWindow NameToWindowMap
//----------------------------------------------------------------------
std::map<std::string, tWindow *> &tWindow::NameToWindowMap()
{
  static std::map<std::string, tWindow *> static_result;
  return static_result;
}

//----------------------------------------------------------------------
// tWindow GetInstance
//----------------------------------------------------------------------
tWindow &tWindow::GetInstance(const std::string &name, unsigned int width, unsigned int height)
{
  if (NameToWindowMap().find(name) == NameToWindowMap().end())
  {
    NameToWindowMap()[name] = new tWindow(name, width, height);
  }
  return *NameToWindowMap()[name];
}

tWindow &tWindow::GetInstance(const std::string &name)
{
  assert(NameToWindowMap().find(name) != NameToWindowMap().end());
  return *NameToWindowMap()[name];
}

tWindow &tWindow::GetInstance()
{
  assert(!NameToWindowMap().empty());
  return *NameToWindowMap().begin()->second;
}

//----------------------------------------------------------------------
// tWindow ReleaseAllInstances
//----------------------------------------------------------------------
void tWindow::ReleaseAllInstances()
{
  for (std::map<std::string, tWindow *>::iterator it = NameToWindowMap().begin(); it != NameToWindowMap().end(); it++)
  {
    delete it->second;
  }
  NameToWindowMap().clear();
}

//----------------------------------------------------------------------
// tWindow Render
//----------------------------------------------------------------------
void tWindow::Render(unsigned int delay) const
{
  cvShowImage(this->name.c_str(), this->image);

  if (!delay)
  {
    std::cout << "[Press key to continue or q to quit]" << std::endl;
  }

  int key = cvWaitKey(delay);

  if (key == 113 || key == 1048689)
  {
    exit(EXIT_SUCCESS);
  }
}

//----------------------------------------------------------------------
// tWindow SetColor
//----------------------------------------------------------------------
void tWindow::SetColor(unsigned char r, unsigned char g, unsigned char b)
{
  this->r = r;
  this->g = g;
  this->b = b;
}

void tWindow::SetColor(unsigned int index)
{
  index %= cNUMBER_OF_COLORS;
  this->SetColor(cPREDEFINED_COLORS[index].red, cPREDEFINED_COLORS[index].green, cPREDEFINED_COLORS[index].blue);
}

//----------------------------------------------------------------------
// tWindow DrawPoint
//----------------------------------------------------------------------
void tWindow::DrawPoint(unsigned int x, unsigned int y)
{
  assert(x <= this->width && y <= this->height);
  y = this->height - y;
  (this->image->imageData + y * this->image->widthStep + x * this->image->nChannels)[0] = this->b;
  (this->image->imageData + y * this->image->widthStep + x * this->image->nChannels)[1] = this->g;
  (this->image->imageData + y * this->image->widthStep + x * this->image->nChannels)[2] = this->r;
}

void tWindow::DrawPoint(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b)
{
  this->SetColor(r, g, b);
  this->DrawPoint(x, y);
}

//----------------------------------------------------------------------
// tWindow DrawPointNormalized
//----------------------------------------------------------------------
void tWindow::DrawPointNormalized(double x, double y)
{
  this->DrawPoint((unsigned int)(x * this->width), (unsigned int)(y * this->height));
}

void tWindow::DrawPointNormalized(double x, double y, unsigned char r, unsigned char g, unsigned char b)
{
  this->SetColor(r, g, b);
  this->DrawPointNormalized(x, y);
}

//----------------------------------------------------------------------
// tWindow DrawLine
//----------------------------------------------------------------------
void tWindow::DrawLine(unsigned int start_x, unsigned int start_y, unsigned int stop_x, unsigned int stop_y)
{
  start_y = this->height - start_y;
  stop_y = this->height - stop_y;
  cvLine(this->image, cvPoint(start_x, start_y), cvPoint(stop_x, stop_y), cvScalar(this->b, this->g, this->r, 0));
}

void tWindow::DrawLine(unsigned int start_x, unsigned int start_y, unsigned int stop_x, unsigned int stop_y, unsigned char r, unsigned char g, unsigned char b)
{
  this->SetColor(r, g, b);
  this->DrawLine(start_x, start_y, stop_x, stop_y);
}

//----------------------------------------------------------------------
// tWindow DrawLineNormalized
//----------------------------------------------------------------------
void tWindow::DrawLineNormalized(double start_x, double start_y, double stop_x, double stop_y)
{
  this->DrawLine((unsigned int)(start_x * this->width), (unsigned int)(start_y * this->height), (unsigned int)(stop_x * this->width), (unsigned int)(stop_y * this->height));
}

void tWindow::DrawLineNormalized(double start_x, double start_y, double stop_x, double stop_y, unsigned char r, unsigned char g, unsigned char b)
{
  this->SetColor(r, g, b);
  this->DrawLineNormalized(start_x, start_y, stop_x, stop_y);
}

//----------------------------------------------------------------------
// tWindow DrawRectangle
//----------------------------------------------------------------------
void tWindow::DrawRectangle(unsigned int min_x, unsigned int min_y, unsigned int max_x, unsigned int max_y)
{
  min_y = this->height - min_y;
  max_y = this->height - max_y;
  cvRectangle(this->image, cvPoint(min_x, min_y), cvPoint(max_x, max_y), cvScalar(this->b, this->g, this->r, 0));
}

void tWindow::DrawRectangle(unsigned int min_x, unsigned int min_y, unsigned int max_x, unsigned int max_y, unsigned char r, unsigned char g, unsigned char b)
{
  this->SetColor(r, g, b);
  this->DrawRectangle(min_x, min_y, max_x, max_y);
}

//----------------------------------------------------------------------
// tWindow DrawRectangleNormalized
//----------------------------------------------------------------------
void tWindow::DrawRectangleNormalized(double min_x, double min_y, double max_x, double max_y)
{
  this->DrawRectangle((unsigned int)(min_x * this->width), (unsigned int)(min_y * this->height), (unsigned int)(max_x * this->width), (unsigned int)(max_y * this->height));
}

void tWindow::DrawRectangleNormalized(double min_x, double min_y, double max_x, double max_y, unsigned char r, unsigned char g, unsigned char b)
{
  this->SetColor(r, g, b);
  this->DrawRectangleNormalized(min_x, min_y, max_x, max_y);
}

//----------------------------------------------------------------------
// tWindow DrawCircle
//----------------------------------------------------------------------
void tWindow::DrawCircle(unsigned int x, unsigned int y, unsigned int radius, bool filled)
{
  y = this->height - y;
  cvCircle(this->image, cvPoint(x, y), radius, cvScalar(this->b, this->g, this->r, 0), filled ? -1 : 1);
}

void tWindow::DrawCircle(unsigned int x, unsigned int y, unsigned int radius, bool filled, unsigned char r, unsigned char g, unsigned char b)
{
  this->SetColor(r, g, b);
  this->DrawCircle(x, y, radius, filled);
}

//----------------------------------------------------------------------
// tWindow DrawCircleNormalized
//----------------------------------------------------------------------
void tWindow::DrawCircleNormalized(double x, double y, double radius, bool filled)
{
  this->DrawCircle((unsigned int)(x * this->width), (unsigned int)(y * this->height), (unsigned int)(radius * sqrt(this->width * this->height)), filled);
}

void tWindow::DrawCircleNormalized(double x, double y, double radius, bool filled, unsigned char r, unsigned char g, unsigned char b)
{
  this->SetColor(r, g, b);
  this->DrawCircleNormalized(x, y, radius, filled);
}

//----------------------------------------------------------------------
// tWindow Clear
//----------------------------------------------------------------------
void tWindow::Clear()
{
  size_t n = this->image->height * this->image->width * this->image->nChannels;
  for (size_t i = 0; i < n; i++)
  {
    this->image->imageData[i] = 255;
  }
  this->SetColor(0, 0, 0);
}
