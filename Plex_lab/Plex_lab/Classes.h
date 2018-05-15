#pragma once
#include<stack>
#include<math.h>

using namespace std;
using namespace System::Drawing;

class TRoot;
class TChart;
class TPoint;

struct TCurrLine
{
	TChart *tc;
	TPoint *pB;
	TPoint *pE;
};

class TRoot
{
protected:
	bool visible;
	bool active;

public:
	TRoot()
	{
		visible = false;
		active = false;
	}

	virtual void Show(Graphics^gr) = 0;
	virtual void Hide(Graphics^gr) = 0;
	virtual void Move(Graphics^gr, int dx, int dy) = 0;
};

class TPoint : public TRoot
{
protected:
	int x, y;

public:
	TPoint(int _x = 0, int _y = 0)
	{
		x = _x;
		y = _y;
	}

	int GetX()
	{
		return x;
	}

	int GetY()
	{
		return y;
	}

	virtual void Show(Graphics^gr)
	{
		gr->DrawEllipse(Pens::Black, x - 2, y - 2, x + 2, y + 2);
		visible = true;
	}

	virtual void Hide(Graphics^gr)
	{
		gr->DrawEllipse(Pens::White, x - 2, y - 2, x + 2, y + 2);
		visible = false;
	}

	virtual void Move(Graphics^gr, int dx, int dy)
	{
		Hide(gr);
		x += dx;
		y += dy;
		Show(gr);
	}
};

class TLine : public TPoint
{
protected:
	int x2, y2;

public:
	virtual void Show(Graphics^gr)
	{
		gr->DrawLine(Pens::Black, x, y, x2, y2);
		visible = true;
	}

	virtual void Hide(Graphics^gr)
	{
		gr->DrawLine(Pens::Black, x, y, x2, y2);
		visible = false;
	}

	virtual void Move(Graphics^gr, int dx, int dy)
	{
		Hide(gr);
		x += dx;
		y += dy;
		x2 += dx;
		y2 += dy;
		Show(gr);
	}
};

class TChart : public TRoot
{
protected:
	TRoot*pBegin, *pEnd;
	bool first;
	stack<TCurrLine> st;
public:
	TChart*pRes;
public:
	TChart(TRoot*pB = nullptr, TRoot*pE = nullptr)
	{
		pBegin = pB;
		pEnd = pE;
	}

	void SetBegin(TRoot*pB)
	{
		TPoint*tp = dynamic_cast<TPoint*>(pB);
		TChart*tc = dynamic_cast<TChart*>(pB);

		if (tp != nullptr||tc != nullptr)
			pBegin = pB;
	}

	TRoot* GetBegin()
	{
		return pBegin;
	}

	void SetEnd(TRoot*pE)
	{
		TPoint*tp = dynamic_cast<TPoint*>(pE);
		TChart*tc = dynamic_cast<TChart*>(pE);

		if (tp != nullptr || tc != nullptr)
			pEnd = pE;
	}

	TRoot* GetEnd()
	{
		return pEnd;
	}

	bool IsFirst()
	{
		return first;
	}

	TRoot*Show(Graphics^gr, TRoot *curr)
	{
		TPoint *tp, *pB, *pE;
		TChart *tc;

		tp = dynamic_cast<TPoint *>(curr);
		tc = dynamic_cast<TChart *>(curr);

		if (tp) {
			tp->Show(gr);
			return curr;
		}
		if (tc) {
			pB = dynamic_cast<TPoint *>(Show(gr, tc->pBegin));
			pE = dynamic_cast<TPoint *>(Show(gr, tc->pEnd));

			if (pB && pE) {
				gr->DrawLine(Pens::Black, pB->GetX(), pB->GetY(), pE->GetX(), pE->GetY());
				return tc->pEnd;
			}
		}
		return nullptr;
	}

	void Show(Graphics^gr)
	{
		TPoint*tmp;
		TCurrLine curr;
		curr.tc = this;
		curr.pB = nullptr;
		curr.pE = nullptr;
		
		while (!st.empty())
			st.pop();

		st.push(curr);
		while (!st.empty())
		{
			curr = st.top();
			st.pop();

			while (curr.pB == nullptr)
			{
				tmp = dynamic_cast<TPoint*>(curr.tc->pBegin);
				if (tmp != nullptr)
					curr.pB = tmp;
				else 
				{
					st.push(curr);
					curr.tc =(TChart*)curr.tc->pBegin;
				}
			}
			if (curr.pE == nullptr)
			{
				tmp = dynamic_cast<TPoint*>(curr.tc->pEnd);
				if (tmp != nullptr)
					curr.pE = tmp;
				else {
					st.push(curr);
					curr.tc = (TChart*)curr.tc->pEnd;
					curr.pB = nullptr;
					st.push(curr);
				}
			}
			if (curr.pB && curr.pE) 
			{
				gr->DrawLine(Pens::Black, curr.pB->GetX(), curr.pB->GetY(), curr.pE->GetX(), curr.pE->GetY());

				tmp = curr.pE;

				if (!st.empty()) {
					curr = st.top();
					st.pop();

					if (!curr.pB) {
						curr.pB = tmp;
					}
					else {
						curr.pE = tmp;
					}

					st.push(curr);
				}
			}
		}
	}

	void Hide(Graphics^gr)
	{
		TPoint*tmp;
		TCurrLine curr;
		curr.tc = this;
		curr.pB = nullptr;
		curr.pE = nullptr;

		while (!st.empty())
			st.pop();

		st.push(curr);
		while (!st.empty())
		{
			curr = st.top();
			st.pop();

			while (curr.pB == nullptr)
			{
				tmp = dynamic_cast<TPoint*>(curr.tc->GetBegin());
				if (tmp != nullptr)
					curr.pB = tmp;
				else
				{
					st.push(curr);
					curr.tc = (TChart*)curr.tc->GetBegin();
				}
			}
			if (curr.pE == nullptr)
			{
				tmp = dynamic_cast<TPoint*>(curr.tc->GetEnd());
				if (tmp != nullptr)
					curr.pE = tmp;
				else {
					st.push(curr);
					curr.tc = (TChart*)curr.tc->GetEnd();
					curr.pB = nullptr;
					st.push(curr);
				}
			}
			if (curr.pB && curr.pE)
			{
				gr->DrawLine(Pens::White, curr.pB->GetX(), curr.pB->GetY(), curr.pE->GetX(), curr.pE->GetY());

				tmp = curr.pE;

				if (!st.empty()) {
					curr = st.top();
					st.pop();

					if (!curr.pB) {
						curr.pB = tmp;
					}
					else {
						curr.pE = tmp;
					}

					st.push(curr);
				}
			}
		}
	}

	void Move(Graphics^gr, int dx, int dy)
	{
		Hide(gr);

		pBegin->Move(gr, dx, dy);
		pEnd->Move(gr, dx, dy);

		Show(gr);
	}

	bool Find(int _x, int _y)
	{
		TPoint*tmp;
		TCurrLine curr;
		curr.tc = this;
		curr.pB = nullptr;
		curr.pE = nullptr;

		while (!st.empty())
			st.pop();

		st.push(curr);
		while (!st.empty())
		{
			curr = st.top();
			st.pop();

			while (curr.pB == nullptr)
			{
				tmp = dynamic_cast<TPoint*>(curr.tc->pBegin);
				if (tmp != nullptr)
					curr.pB = tmp;
				else
				{
					st.push(curr);
					curr.tc = (TChart*)curr.tc->pBegin;
				}
			}
			if (curr.pE == nullptr)
			{
				tmp = dynamic_cast<TPoint*>(curr.tc->pEnd);
				if (tmp != nullptr)
					curr.pE = tmp;
				else {
					st.push(curr);
					curr.tc = (TChart*)curr.tc->pEnd;
					curr.pB = nullptr;
					st.push(curr);
				}
			}
			if (curr.pB != nullptr && curr.pE != nullptr)
			{
				if (abs(curr.pB->GetX() - _x) < 10 && abs(curr.pB->GetY() - _y) < 10)
				{
					pRes = curr.tc;
					first = true;
					return true;
				}

				if (abs(curr.pE->GetX() - _x) < 10 && abs(curr.pE->GetY() - _y) < 10)
				{
					pRes = curr.tc;
					first = false;
					return true;
				}

				tmp = curr.pE;

				if (!st.empty())
				{
					curr = st.top();
					st.pop();

					if (!curr.pB) {
						curr.pB = tmp;
					}
					else {
						curr.pE = tmp;
					}

					st.push(curr);
				}
			}
		}
		return false;
	}
};
