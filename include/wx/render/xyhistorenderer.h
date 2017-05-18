/////////////////////////////////////////////////////////////////////////////
// Name:    xyhistorenderer.h
// Purpose: xy histogram renderer declarations
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef XYHISTORENDERER_H_
#define XYHISTORENDERER_H_

#include <wx/xy/xyrenderer.h>
#include <wx/areadraw.h>

/**
 * Renderer for displaying XY data as histograms.
 */
class WXDLLIMPEXP_FREECHART XYHistoRenderer : public XYRenderer
{
    DECLARE_CLASS(XYHistoRenderer)
public:
    /**
     * Constructs new XYHistoRenderer.
     * @param barWidth width to histogram bars
     * @param vertical true to draw vertical bars, false - to horizontal
     */
    XYHistoRenderer(int barWidth = 10, bool vertical = true);
    virtual ~XYHistoRenderer();

    virtual void Draw(wxDC&dc, const wxRect& rc, Axis* xAxis, Axis* yAxis, BiDataSet* dataset);

    /**
     * Set area fill to draw specified serie.
     * XYHistoRenderer takes ownership of barArea.
     * @param serie serie index
     * @param barArea area background object to draw bars
     */
    void SetBarArea(size_t serie, AreaDraw *barArea);

    /**
     * Returns area draw for specified serie.
     * @param serie serie index
     * @return area draw for specified serie
     */
    AreaDraw *GetBarArea(size_t serie);

    virtual double GetMax(const Dataset* dataset, size_t dimension) const { return 100; };
    virtual double GetMin(const Dataset* dataset, size_t dimension) const { return 0; };

    //
    // DrawObserver
    //
    virtual void NeedRedraw(DrawObject *obj);

private:
    void DrawBar(int serie, wxDC &dc, wxRect rcData, wxCoord x, wxCoord y);

    int m_barWidth;
    bool m_vertical;

    wxCoord m_serieShift;

    AreaDrawCollection m_barAreas;
};

#endif /*XYHISTORENDERER_H_*/