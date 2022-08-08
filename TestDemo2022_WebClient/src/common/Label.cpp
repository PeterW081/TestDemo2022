#include "Label.h"

Label::Label(QWidget* parent, Qt::WindowFlags f)
	: QLabel(parent, f)
{
}

void Label::mouseReleaseEvent(QMouseEvent* ev)
{
	emit clicked();
}
