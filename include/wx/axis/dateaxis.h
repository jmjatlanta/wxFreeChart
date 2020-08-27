/////////////////////////////////////////////////////////////////////////////
// Name:    dateaxis.h
// Purpose: Date/time axis declaration
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef DATEAXIS_H_
#define DATEAXIS_H_

#include <wx/axis/labelaxis.h>


/**
 * An axis for displaying date/time values.
 * TODO:
 * - works with only one dataset.
 */
class WXDLLIMPEXP_FREECHART DateAxis : public LabelAxis
{
    DECLARE_CLASS(DateAxis)
public:
    DateAxis(AXIS_LOCATION location);
    virtual ~DateAxis();

   /****
    * Fire the BoundsChanged event if the dataset size has increased
    * @returns true if the FireBoundsChanged method was called
    */
    virtual bool UpdateBounds() wxOVERRIDE;

    /**
     * Sets date format for date labels.
     * @param dateFormat date format in strftime style
     */
    void SetDateFormat(const wxString &dateFormat)
    {
        m_dateFormat = dateFormat;
        FireAxisChanged();
    }

   /***
    * Get the bounds of the data
    * @param minValue the minimum value (always zero)
    * @param maxValue the number of records in the dataset
    */
    virtual void GetDataBounds(double &minValue, double &maxValue) const;

protected:
    /***
     * Accepts only 1 date dataset
     * @param dataset the dataset
     * @returns true if accepted
     */
    virtual bool AcceptDataset(Dataset *dataset);

   /****
    * Returns step as a double
    * @param step the step
    * @returns step
    */
    virtual double GetValue(size_t step);

   /***
    * Get the label for a given step
    * @param step the step
    * @param label the label that was found for that step
    */
    virtual void GetLabel(size_t step, wxString &label);

   /***
    * See if the step is greater than or equal to the size of the dataset
    * @param step the step
    * @returns true if we're out of steps
    */
    virtual bool IsEnd(size_t step);

   /*****
    * For the drawing context, get the size of the longest label
    * @param dc the drawing context
    * @returns the size of the longest label
    */
    virtual wxSize GetLongestLabelExtent(wxDC &dc);

private:
    size_t m_dateCount; // number of data items
    wxString m_dateFormat; // the format of the date in the label
};

#endif /*DATEAXIS_H_*/
