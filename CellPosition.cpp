#include "CellPosition.h"
#include "UI_Info.h"

CellPosition::CellPosition () 
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1; 
	hCell = -1; 
}

CellPosition::CellPosition (int v, int h)
{ 
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1; 
	hCell = -1; 

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition (int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum); // the function call with build a cell position (vCell and hCell)
												// from the passed (cellNum)
												// (*this) = ... --> this will copy the returned (vCell and hCell)
												//                   to the data members (vCell and hCell)
}

bool CellPosition::SetVCell(int v) 
{
	if (v < 0 || v>8) {
		return false;
	}
	else { vCell = v; return true; }
}

bool CellPosition::SetHCell(int h) 
{
	if (h < 0 || h>10) {
		return false;
	}
	else { hCell = h; return true; }
}

int CellPosition::VCell() const 
{
	return vCell;
}

int CellPosition::HCell() const 
{
	return hCell;
}

bool CellPosition::IsValidCell() const 
{
	if (hCell <= 0 || hCell>=10) {
		if (vCell <= 0 || vCell>=8)return true;
	}
	else return false;
	
}

int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this); // (*this) is the calling object of GetCellNum
										  // which means the object of the current data members (vCell and hCell)
}

int CellPosition::GetCellNumFromPosition(const CellPosition & cellPosition)
{
	int CellNum;
	if (cellPosition.IsValidCell() == 1) {
		CellNum = (cellPosition.HCell() + 1) + (8 - cellPosition.VCell()) * NumHorizontalCells;
			return CellNum;
	
	}

	

	return false; 
}

CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{

	CellPosition position;

	if (cellNum >= 1 && cellNum <= NumHorizontalCells * NumVerticalCells) {
		position.SetHCell((cellNum % NumHorizontalCells == 0) ? (NumHorizontalCells - 1) : (cellNum % NumHorizontalCells - 1));
		position.SetVCell((cellNum % NumHorizontalCells == 0) ? (NumVerticalCells - cellNum / NumHorizontalCells) : (NumVerticalCells - 1 - cellNum / NumHorizontalCells));
	}
	//If the function takes an invalid cellNum it uses Default Constructor, vCell = -1 and hCell = -1
	return position;
}

void CellPosition::AddCellNum (int addedNum)
{
	int new_num = min(GetCellNum()+addedNum, NumHorizontalCells * NumVerticalCells); // to avoid invaid numbers such as greater than 100 or less than 0
    CellPosition new_position = GetCellPositionFromNum(new_num); //to change vCell and Hcell into new position
	SetVCell(new_position.VCell());
	SetHCell(new_position.HCell());
}