//
// You received this file as part of RRLib
// Robotics Research Library
//
// Copyright (C) AG Robotersysteme TU Kaiserslautern
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
/*!\file    tWindow.h
 *
 * \author  Tobias Foehst
 * \date    2008-12-26
 *
 * \brief   Contains tWindow
 *
 * \b tWindow
 *
 * A few words for tWindow
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__highgui__wrapper__tWindow_h__
#define __rrlib__highgui__wrapper__tWindow_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <iostream>
#include <string>
#include <map>

#include <cv.h>

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Debugging
//----------------------------------------------------------------------
#include <cassert>

//----------------------------------------------------------------------
// Namespace declaration
//----------------------------------------------------------------------
namespace rrlib
{
namespace highgui
{

//----------------------------------------------------------------------
// Forward declarations / typedefs / enums
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Class declaration
//----------------------------------------------------------------------
//! Short description of tBoundingBox
/*! A more detailed description of tBoundingBox, which
    Tobias Foehst hasn't done yet !!
*/
class tWindow
{

//----------------------------------------------------------------------
// Public methods and typedefs
//----------------------------------------------------------------------
public:

  static tWindow &GetInstance(const std::string &name, unsigned int width, unsigned int height);
  static tWindow &GetInstance(const std::string &name);
  static tWindow &GetInstance();

  static void ReleaseAllInstances();

  void Render() const;

  void SetColor(unsigned char r, unsigned char g, unsigned char b);
  void SetColor(unsigned int index);

  void DrawPoint(unsigned int x, unsigned int y);
  void DrawPoint(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b);

  void DrawPointNormalized(double x, double y);
  void DrawPointNormalized(double x, double y, unsigned char r, unsigned char g, unsigned char b);

  void DrawLine(unsigned int start_x, unsigned int start_y, unsigned int stop_x, unsigned int stop_y);
  void DrawLine(unsigned int start_x, unsigned int start_y, unsigned int stop_x, unsigned int stop_y, unsigned char r, unsigned char g, unsigned char b);

  void DrawLineNormalized(double start_x, double start_y, double stop_x, double stop_y);
  void DrawLineNormalized(double start_x, double start_y, double stop_x, double stop_y, unsigned char r, unsigned char g, unsigned char b);

  void DrawRectangle(unsigned int min_x, unsigned int min_y, unsigned int max_x, unsigned int max_y);
  void DrawRectangle(unsigned int min_x, unsigned int min_y, unsigned int max_x, unsigned int max_y, unsigned char r, unsigned char g, unsigned char b);

  void DrawRectangleNormalized(double min_x, double min_y, double max_x, double max_y);
  void DrawRectangleNormalized(double min_x, double min_y, double max_x, double max_y, unsigned char r, unsigned char g, unsigned char b);

  void DrawCircle(unsigned int x, unsigned int y, unsigned int radius, bool filled);
  void DrawCircle(unsigned int x, unsigned int y, unsigned int radius, bool filled, unsigned char r, unsigned char g, unsigned char b);

  void DrawCircleNormalized(double x, double y, double radius, bool filled);
  void DrawCircleNormalized(double x, double y, double radius, bool filled, unsigned char r, unsigned char g, unsigned char b);

  void Clear();

//----------------------------------------------------------------------
// Private fields and methods
//----------------------------------------------------------------------
private:

  std::string name;
  unsigned int width;
  unsigned int height;
  IplImage *image;
  unsigned char r, g, b;

  static std::map<std::string, tWindow *> &NameToWindowMap();

  tWindow(const std::string &name, unsigned int width, unsigned int height);

  ~tWindow();

};

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}


#endif
