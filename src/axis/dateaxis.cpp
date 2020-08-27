/////////////////////////////////////////////////////////////////////////////
// Name:    dateaxis.cpp
// Purpose: date axis implementation
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/axis/dateaxis.h>

IMPLEMENT_CLASS(DateAxis, Axis)

DateAxis::DateAxis(AXIS_LOCATION location)
: LabelAxis(location)
{
    m_dateFormat = wxT("%d %m");
    m_dateCount = 0;
}

DateAxis::~DateAxis()
{
}

/***
 * Accepts only 1 date dataset
 * @param dataset the dataset
 * @returns true if accepted
 */
bool DateAxis::AcceptDataset(Dataset *dataset)
{
    return (dataset->AsDateTimeDataset() != NULL)
        && (m_datasets.Count() == 0);
}

/****
 * Fire the BoundsChanged event if the dataset size has increased
 * @returns true if the FireBoundsChanged method was called
 */
bool DateAxis::UpdateBounds()
{
   // calculate the size of the dataset
   size_t dateCount = 0;
   for (size_t n = 0; n < m_datasets.Count(); n++) {
      DateTimeDataset *dataset = m_datasets[n]->AsDateTimeDataset();
      size_t count = dataset->GetCount();
      dateCount = wxMax(dateCount, count);
   }

   // if the size has changed, fire the BoundsChanged event and return true
   if (dateCount != m_dateCount) {
      m_dateCount = dateCount;
      FireBoundsChanged();
      return true;
   }
   return false;
}

/*****
 * For the drawing context, get the size of the longest label
 * @param dc the drawing context
 * @returns the size of the longest label
 */
wxSize DateAxis::GetLongestLabelExtent(wxDC &dc)
{
    dc.SetFont(GetLabelTextFont());

    wxSize maxExtent(0, 0);

    for (int step = 0; !IsEnd(step); step++) {
        wxString label;
        GetLabel(step, label);

        wxSize labelExtent = dc.GetTextExtent(label);
        maxExtent.x = wxMax(maxExtent.x, labelExtent.x);
        maxExtent.y = wxMax(maxExtent.y, labelExtent.y);
    }

    return maxExtent;
}

/***
 * Get the bounds of the data
 * @param minValue the minimum value (always zero)
 * @param maxValue the number of records in the dataset
 */
void DateAxis::GetDataBounds(double &minValue, double &maxValue) const
{
    minValue = 0;
    if (m_dateCount > 1) {
        maxValue = m_dateCount - 1;
    }
    else {
        maxValue = 0;
    }
}

/****
 * Returns step as a double
 * @param step the step
 * @returns step
 */
double DateAxis::GetValue(size_t step)
{
    return step;
}

/***
 * Get the label for a given step
 * @param step the step
 * @param label the label that was found for that step
 */
void DateAxis::GetLabel(size_t step, wxString &label)
{
    DateTimeDataset *dataset = m_datasets[0]->AsDateTimeDataset();
    if (dataset == NULL) {
        return ; // BUG
    }

    wxDateTime dt;
    dt.Set(dataset->GetDate(step));
    label = dt.Format(m_dateFormat);
}

/***
 * See if the step is greater than or equal to the size of the dataset
 * @param step the step
 * @returns true if we're out of steps
 */
bool DateAxis::IsEnd(size_t step)
{
    return step >= m_dateCount;
}
