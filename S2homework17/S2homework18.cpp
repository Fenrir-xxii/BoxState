#include <iostream>
#include "Menu.h"

enum BOX_STATE
{
    OPEN = 0, CLOSED, SEALED, SENT, DELIVERED
};

class myException :public std::exception
{
public:
    const char* message;
    std::string errorText;
    myException(std::string msg)
    {
        this->errorText = msg;
    }
    const char* what()
    {
        this->message = errorText.c_str();
        return message;
    }
};

class StateOfBox
{
private:
    BOX_STATE currentState;
    bool isStateChangeValid(BOX_STATE state);
public:
    StateOfBox()
    {
        this->currentState = BOX_STATE::OPEN;
    }
    void setNewState(BOX_STATE state);
    BOX_STATE getCurrentState();
};

bool StateOfBox::isStateChangeValid(BOX_STATE state)
{
    switch (this->currentState)
    {
    case BOX_STATE::OPEN:
        if (state == BOX_STATE::CLOSED)
        {
            return true;
        }
        else
        {
            return false;
        }
        break;
    case BOX_STATE::CLOSED:
        if (state == BOX_STATE::OPEN or state == BOX_STATE::SEALED)
        {
            return true;
        }
        else
        {
            return false;
        }
        break;
    case BOX_STATE::SEALED:
        if (state == BOX_STATE::SENT)
        {
            return true;
        }
        else
        {
            return false;
        }
        break;
    case BOX_STATE::SENT:
        if (state == BOX_STATE::DELIVERED)
        {
            return true;
        }
        else
        {
            return false;
        }
        break;
    case BOX_STATE::DELIVERED:
        if (state == BOX_STATE::OPEN)
        {
            return true;
        }
        else
        {
            return false;
        }
        break;
    default:
        return false;
    }
}

void StateOfBox::setNewState(BOX_STATE state)
{
    bool isNextStateValid = isStateChangeValid(state);
    std::string msg;
    if (isNextStateValid)
    {
        this->currentState = state;
    }
    else
    {
        std::string state;
        std::string options;
        switch (this->currentState)
        {
        case BOX_STATE::OPEN:
            state = "open";
            options = "close";
            break;
        case BOX_STATE::CLOSED:
            state = "closed";
            options = "open or seal";
            break;
        case BOX_STATE::SEALED:
            state = "sealed";
            options = "send";
            break;
        case BOX_STATE::SENT:
            state = "sent";
            options = "deliver";
            break;
        case BOX_STATE::DELIVERED:
            state = "delivered";
            options = "open";
            break;
        }
        msg = "Current state of box is " + state + ".\nYou can " + options + " the box";
        throw myException(msg);
    }
}

BOX_STATE StateOfBox::getCurrentState()
{
    return this->currentState;
}

class Box
{
private:
    StateOfBox state;
public:
    void openBox();
    void closeBox();
    void sealBox();
    void sendBox();
    void deliverBox();
    BOX_STATE getCurrentState();
};

void Box::openBox()
{
    this->state.setNewState(BOX_STATE::OPEN);
}

void Box::closeBox()
{
    this->state.setNewState(BOX_STATE::CLOSED);
}

void Box::sealBox()
{
    this->state.setNewState(BOX_STATE::SEALED);
}

void Box::sendBox()
{
    this->state.setNewState(BOX_STATE::SENT);
}

void Box::deliverBox()
{
    this->state.setNewState(BOX_STATE::DELIVERED);
}

BOX_STATE Box::getCurrentState()
{
    return this->state.getCurrentState();
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void drawData(int x, int y, std::string message)
{
    SetCursorPosition(x, y);
    std::cout << std::string(x + 10, ' ');
    SetCursorPosition(x, y);
    std::cout << message;
    SetCursorPosition(0, 0);
}

std::string getStateString(BOX_STATE state)
{
    std::string result;
    switch (state)
    {
    case BOX_STATE::OPEN:
        result = "open";
        break;
    case BOX_STATE::CLOSED:
        result = "closed";
        break;
    case BOX_STATE::SEALED:
        result = "sealed";
        break;
    case BOX_STATE::SENT:
        result = "sent";
        break;
    case BOX_STATE::DELIVERED:
        result = "delivered";
        break;
    }

    return result;
}

int main()
{
    ShowConsoleCursor(false);

    std::vector<std::string> options({ "Open", "Close", "Seal", "Send", "Deliver" });
    Menu menu(options);
    Box myBox;

    int key = -1;
    int selection = -1;
    BOX_STATE currentStateOfBox = myBox.getCurrentState();
    std::string message = "Current state of box is: ";
    std::string state = getStateString(currentStateOfBox);

    drawData(30, 0, message + state);

    while (key != ESC)
    {
        menu.drawFrame();
        menu.drawOptions();
        key = getKey();

        switch (key)
        {
        case UP_ARROW:
            menu.up();
            break;
        case DOWN_ARROW:
            menu.down();
            break;
        case ENTER:
            selection = menu.getSelectedOption();
            try
            {
                if (selection == BOX_STATE::OPEN)
                {
                    myBox.openBox();
                }
                else if (selection == BOX_STATE::CLOSED)
                {
                    myBox.closeBox();
                }
                else if (selection == BOX_STATE::SEALED)
                {
                    myBox.sealBox();
                }
                else if (selection == BOX_STATE::SENT)
                {
                    myBox.sendBox();
                }
                else if (selection == BOX_STATE::DELIVERED)
                {
                    myBox.deliverBox();
                }
            }
            catch (myException e)
            {
                system("cls");
                std::cout << e.what() << std::endl << std::endl;
                system("pause");
                system("cls");
            }
            currentStateOfBox = myBox.getCurrentState();
            state = getStateString(currentStateOfBox);
            drawData(30, 0, message + state);
            break;
        case ESC:
            system("cls");
            break;
        default:
            break;
        }
    }

}