#include "utilsShell.h"

#include <iostream>
#include <string>
#include <utility>

#include <conio.h>
#include <stdio.h>
#include <time.h>

extern const utils::shell::tShellCommandList ShellCommandList[];

class tDevShell;

tDevShell* g_pDevShell = nullptr;

class tDevShell : public utils::shell::tShell
{
public:
	explicit tDevShell(const utils::shell::tShellCommandList* cmdList)
		:utils::shell::tShell(cmdList)
	{
		g_pDevShell = this;

		OnShell();//
	}

	virtual ~tDevShell()
	{
		g_pDevShell = nullptr;
	}

	static bool Handler1(const std::vector<std::string>& data)
	{
		std::cout << "Handler1" << std::endl;

		ShowReceivedCmd(data);

		return true;
	}

	static bool Handler2(const std::vector<std::string>& data)
	{
		std::cout << "Handler2" << std::endl;

		ShowReceivedCmd(data);

		if (data.size() == 1)
		{
			const char MenuFormat[] = " %-20s %s\n";

			for (unsigned int i = 0; i < LIB_UTILS_SHELL_MENU_ITEM_QTY_MAX; ++i)
			{
				if (ShellCommandList[i].Command == 0)
				{
					break;
				}

				if (ShellCommandList[i].Command[0] == '~')//Hidden line
				{
					////////////////////////////////
					//Hidden menu
					std::cout << " hidden line ---- !!!" << std::endl;
					////////////////////////////////
					////////////////////////////////
				}
				else
				{
					printf(MenuFormat, ShellCommandList[i].Command, ShellCommandList[i].Description);
				}
			}

			return true;
		}

		return false;
	}

	static bool Debug;

	static bool Handler3(const std::vector<std::string>& data)
	{
		std::cout << "Handler3" << std::endl;

		ShowReceivedCmd(data);

		Debug = !Debug;

		return true;
	}

	static bool Handler4(const std::vector<std::string>& data)
	{
		std::cout << "Handler4" << std::endl;

		if (data.size() > 1 && g_pDevShell)
		{
			g_pDevShell->SetEcho(data[1] != "0");

			return true;
		}

		return false;
	}

protected:
	virtual void Board_Send(char data) const
	{
		std::cout << data;
	}

	virtual void Board_Send(const std::vector<char>& data) const
	{
		for (size_t i = 0; i < data.size(); ++i)
		{
			std::cout << data[i];
		}
	}

	virtual void OnShell() const
	{
		if (Debug)
		{
			std::cout << "debug>>";
		}
		else
		{
			std::cout << "shell>>";
		}
	}

	virtual void OnFailed(std::vector<std::string>& data) const
	{
		std::cout << "OnFailed:" << std::endl;

		ShowReceivedCmd(data);
	}

private:
	static void ShowReceivedCmd(const std::vector<std::string>& data)
	{
		for (size_t i = 0; i < data.size(); ++i)
		{
			std::cout << i << " " << data[i] << std::endl;
		}
	}
};

bool tDevShell::Debug = false;

const utils::shell::tShellCommandList ShellCommandList[] =
{
	{ (char*)"help",   (char*)"blablabla", tDevShell::Handler1 },
	{ (char*)"?",      (char*)"la-la-la",  tDevShell::Handler2 },
	{ (char*)"~2",     (char*)"bla-bla",   tDevShell::Handler3 },
	{ (char*)"~debug", (char*)"DEBUG",     tDevShell::Handler3 },
	{ (char*)"echo",   (char*)"ECHO 0-off, 1-on",      tDevShell::Handler4 },
	{ 0 }
};

int main()
{
	tDevShell Shell(ShellCommandList);

	while (true)
	{
		//int Byte = getch();
		int Byte = getchar();

		Shell.Board_OnReceived(static_cast<char>(Byte));
	}

	system("pause");

	return 0;
}