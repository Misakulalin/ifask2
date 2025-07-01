#include "global.h"

global::global() {}//全局刷新错误提示
std::function<void(QWidget*)> repolish=[](QWidget*w)//lambda表达式捕捉<返回值<参数<类型>>
{
    w->style()->unpolish(w);
    w->style()->polish(w);
};
