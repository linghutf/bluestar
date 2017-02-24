#include "handler.hh"

void select_doc(Handle & h);
void select_lib(Handle & h);

int main(int argc, char *argv[])
{
    Handle h;
    h.init_from_file();
    std::cout<<"系统初始化完成...\n\n";
    int choice;
    bool done = false;
    while(!done)
    {
        std::cout<<"1. 记录\n2. 档案\n3. 退出\n\n选择[1~3]:";
        std::cin>>choice;
        switch(choice)
        {
            case 1:select_doc(h);break;
            case 2:select_lib(h);break;
            case 3:done = true;
            default:break;
        }
    }
    h.save_to_file();
    return 0;
}

void select_doc(Handle & h)
{
    int c;
    bool done = false;
    std::string name;
    while(!done)
    {
        std::cout<<"1. 查看\n2. 添加\n3. 修改\n4. 删除\n5. 返回\n\n选择[1-5]:";
        std::cin>>c;
        switch(c)
        {
            case 2:
                std::cout<<"添加主题:";
                std::cin>>name;
                if(h.add_todo(name))
                {
                    std::cout<<"成功!\n";
                }
                break;
            case 1:
                h.view_records();
                break;
            case 3:
                std::cout<<"修改主题:";
                std::cin>>name;
                if(h.update_todo(name))
                {
                    std::cout<<"成功!\n";
                }
                break;
            case 4:
                std::cout<<"删除主题:";
                h.list_all_todo();
                std::cin>>name;
                h.del_todo(name);
                break;
            case 5:
                done=true;break;
            default:break;
        }
    }
}

void select_lib(Handle & h)
{
    std::string name;
    int c;
    bool done=false;
    while(!done)
    {
        std::cout<<"1. 查看\n2. 添加\n3. 修改\n4. 返回\n\n选择[1-4]:";
        std::cin>>c;
        switch(c)
        {
            case 1:
                h.view_items();
                break;
            case 2:
                std::cout<<"添加条目:";
                std::cin>>name;
                if(h.add_item(name))
                {
                    std::cout<<"成功!\n";
                }
                break;
            case 3:
                std::cout<<"修改条目:";
                std::cin>>name;
                if(h.update_item(name))
                {
                    std::cout<<"成功!\n";
                }
                break;
            case 4:
                done=true;break;
            default:break;
        }
    }
}
