#include "StandardFunctions.h"

/** -------------------------------------- НАЧАЛО ОПИСАНИЯ: КЛАСС "StandardFunctions" -------------------------------------------------------**/

StandardFunctions::StandardFunctions(int* _hWind, int* _hMenu, SDL_Renderer* ren, TTF_Font* font)
{
    hMenu = _hMenu;
    hWind = _hWind;

    input[0] = new Input(ren, font, "Введите коэффициенты", 1, 0, &tempABC.a, NULL, NULL);
    input[1] = new Input(ren, font, "Введите коэффициенты", 2, 0, &tempABC.a, &tempABC.b, NULL);
    input[2] = new Input(ren, font, "Введите коэффициенты", 3, 0, &tempABC.a, &tempABC.b, &tempABC.c);

    h = 60;
    addFunc = -1;
    edit = -1;
    iterElement = 0;

/*str[0] = "y = a / x";   str[1] = " y = x^a"; str[2] = "y = a^x"; */

    str[0] = "y = a / x";        str[1] = " y = x^a";          str[2] = "y = a^x"; str[3] = "y = a·sin(x·b)";  str[4] = "y = a·cos(x·b)";
    str[5] = "y = a·arctg(xb)";  str[6] = "y = a·arcctg(xb)";  str[7] = "y = a·x² + b·x + c";

    SDL_Rect rect = { 25, 100, 266, 35};
    strEl = new StrElementMenu(&str[0], ren, &rect, font, -1);

    rect = { 160 , 185, 40, 25 };
    ub = new UpButton(_hMenu, ren, &rect, 1);

    rect = { 210 , 185, 40, 25 };
    db = new DownButton(_hMenu, ren, &rect, 1);

    LoadStFunc(ren, font);
}

StandardFunctions::~StandardFunctions()
{
    delete input[0];
    delete input[1];
    delete input[2];
    delete strEl;

    int i = st_func.size()-1;
    while(st_func.size())
    {
        delete st_func[i]->stFunc;
        delete st_func[i]->add;
        delete st_func[i];
        st_func.pop_back();
        i--;
    }

    i = stf.size()-1;
    while(stf.size())
    {
        delete stf[i]->stFunc;
        delete stf[i]->edit;
        delete stf[i]->del;
        delete stf[i];
        stf.pop_back();
        i--;
    }

    delete ub;
    delete db;
}

void StandardFunctions::AddFunc(SDL_Event* ev)
{
    if(edit < 0)
    {
        strEl->SetStr(str[addFunc]);
        if(st_func[addFunc]->stFunc->GetType() == 1)
            *hMenu = 225;
        if(st_func[addFunc]->stFunc->GetType() == 2)
            *hMenu = 265;
        if(st_func[addFunc]->stFunc->GetType() == 3)
            *hMenu = 300;
        input[st_func[addFunc]->stFunc->GetType()-1]->InputDate(ev);
    }
    else
    {
        strEl->SetStr(str[edit]);
        if(stf[addFunc]->stFunc->GetType() == 1)
            *hMenu = 225;
        if(stf[addFunc]->stFunc->GetType() == 2)
            *hMenu = 265;
        if(stf[addFunc]->stFunc->GetType() == 3)
            *hMenu = 300;
        input[stf[addFunc]->stFunc->GetType()-1]->InputDate(ev);
    }
    strEl->DrawElement(false);
}

void StandardFunctions::SaveFunc(TTF_Font* font, SDL_Renderer* ren)
{
    StFExample *temp = new StFExample;
    string str = "\0";
    SDL_Rect rect = { 25 , h, 266, 35};

    switch(addFunc)
    {
        case 0 : temp->stFunc = new StFunc1(&h, 1, &str, font, ren, &rect, 0); break;
        case 1 : temp->stFunc = new StFunc2(&h, 1, &str, font, ren, &rect, 1); break;
        case 2 : temp->stFunc = new StFunc3(&h, 1, &str, font, ren, &rect, 2); break;
        case 3 : temp->stFunc = new StFunc4(&h, 2, &str, font, ren, &rect, 3); break;
        case 4 : temp->stFunc = new StFunc5(&h, 2, &str, font, ren, &rect, 4); break;
        case 5 : temp->stFunc = new StFunc6(&h, 2, &str, font, ren, &rect, 5); break;
        case 6 : temp->stFunc = new StFunc7(&h, 2, &str, font, ren, &rect, 6); break;
        case 7 : temp->stFunc = new StFunc8(&h, 3, &str, font, ren, &rect, 7); break;
    }

    temp->stFunc->SetABC(&tempABC.a, &tempABC.b, &tempABC.c);
    temp->stFunc->SetDoubleABC(atof(tempABC.a.c_str()), atof(tempABC.b.c_str()), atof(tempABC.c.c_str()));
    temp->stFunc->UpdateStr();

    rect = { 185, h, 37, 35};
    temp->edit = new EditButton(&h, ren, &rect, 1);

    rect = { 225, h, 37, 35};
    temp->del = new DeleteButton(&h, ren, &rect, 1);

    stf.push_back(temp);

    StopAddFunc();
}

void StandardFunctions::StopAddFunc()
{
    addFunc = -1;
    edit = -1;
    tempABC.a.clear();
    tempABC.b.clear();
    tempABC.c.clear();
}

void StandardFunctions::LoadStFunc(SDL_Renderer* ren, TTF_Font* font)
{
    int type[] = {1, 1, 1, 2, 2, 2, 2, 3};

    StandardFunction *stFunc;
    AddButton *add;
    SDL_Rect rect = { 25 , h, 266, 35 };

    for(int i = 0; i < 8; i++)
    {
        h += 60;
        st_f *st = new st_f;

        rect = { 25 , h, 266, 35 };
        st->stFunc = new StandardFunction(&h, type[i], &str[i], font, ren, &rect, 200+i);

        rect = { 225, h, 37, 35};
        st->add = new AddButton(&h, ren, &rect, 200+i);

        st_func.push_back(st);
    }
}

void StandardFunctions::DeleteFunc(int i)
{
    delete stf[i]->stFunc;
    delete stf[i]->edit;
    delete stf[i]->del;
    delete stf[i];
    stf.erase(stf.begin()+i);
}

void StandardFunctions::EditFunc(int i)
{
    tempABC.a = *stf[i]->stFunc->GetABC(1);
    tempABC.b = *stf[i]->stFunc->GetABC(2);
    tempABC.c = *stf[i]->stFunc->GetABC(3);
}

void StandardFunctions::SaveEdit()
{
    stf[addFunc]->stFunc->SetABC(&tempABC.a, &tempABC.b, &tempABC.c);
    stf[addFunc]->stFunc->SetDoubleABC(atof(tempABC.a.c_str()), atof(tempABC.b.c_str()), atof(tempABC.c.c_str()));
    stf[addFunc]->stFunc->UpdateStr();
    StopAddFunc();
    edit = -1;
}

int StandardFunctions::DrawStFunc(SDL_Event* ev)
{
    h = 60;

    for(int i = 0; i < st_func.size(); i++)
    {
        h += 40;

        if(st_func[i]->add->EventElement(ev) == 200+i)
            addFunc = i;

        st_func[i]->add->DrawElement();

        st_func[i]->stFunc->EventElement(ev);
        st_func[i]->stFunc->DrawElement();
    }
    *hMenu = h + 45;

    return addFunc;
}

void StandardFunctions::DrawGraphs(Keys* keys)
{
    for(int i = 0; i < stf.size(); i++)
    {
        stf[i]->stFunc->DrawGraph(keys);
    }
}

void StandardFunctions::ShowStFunc(SDL_Event* ev)
{
    h = 60;
    int del = -1;
    int i;

    for( i = iterElement; i < stf.size() && h < *hWind - 40; i++)    {
        h += 40;

        if(stf[i]->edit->EventElement(ev) == true)
        {
            edit = stf[i]->stFunc->EventElement(ev);
            addFunc = i;
        }
        else
            stf[i]->stFunc->EventElement(ev);

        if(stf[i]->del->EventElement(ev) == true)
            del = i;

        stf[i]->edit->DrawElement();
        stf[i]->del->DrawElement();
        stf[i]->stFunc->DrawElement();
    }
    if(i < stf.size() && iterElement + 1 < stf.size())
    {
        ub->DrawElement();
        if(ub->EventElement(ev) == true )
            iterElement++;
    }

    if(iterElement > 0 && iterElement - 1 >= 0)
    {
        db->DrawElement();
        if(db->EventElement(ev) == true )
            iterElement--;
    }

    *hMenu = h + 45;

    if(del >= 0)
        DeleteFunc(del);
    if(edit >= 0)
        EditFunc(addFunc);
}

/** -------------------------------------- КОНЕЦ ОПИСАНИЯ: КЛАСС "StandardFunctions" -------------------------------------------------------**/
