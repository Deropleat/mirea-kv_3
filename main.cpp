#include "cl_application_2.h"
// #include "cl_application.h" <- удалите строку выше и раскомментируйте данную строку, если в вашем проекте удален/отсутствует файл cl_application_2 - это по желанию, т.к. ничего не происходит от этого в этой работе!

int main()
{
    cl_application ob_cl_application(nullptr);
    ob_cl_application.bild_tree_objects();
    return ob_cl_application.exec_app();
}
