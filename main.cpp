#include "File.h"
#include "Tui.h"
#include <conio.h>
#include <algorithm>
#include <Windows.h>// for Sleep
void pPractice(const std::string &fileName, const std::string &showName) {
	std::vector<std::string> lines = readLinesFromFile(fileName);
	size_t lineIndex = 0;
	size_t errorCount = 0;
	std::string input = "";
	size_t inputIndex = 0;
	while (1) {
		// 显示练习标题
		IO << TUI::ClearScreen{} << TUI::GotoXY(15, 0) << "练习 " << showName;
		// 显示当前行数
		IO << TUI::GotoXY(0, 11) << "当前行数：" << lineIndex + 1 << "/" << lines.size();
		// 显示错误字符数
		IO << TUI::GotoXY(0, 12) << "当前错误字符数： " << errorCount << " 字";
		// 显示当前要输入的句子
        IO << TUI::GotoXY(6, 4) << "\033[32m" << lines[lineIndex] << "\033[0m";
		// 显示用户输入
		IO << TUI::GotoXY(6, 5) << "\033[4m" << input << TUI::GotoXY(6 + lines[lineIndex].size(), 5) << "\033[0m";
		IO << TUI::GotoXY(15, 2) << "按ESC退出";
		IO << TUI::GotoXY(6 + input.size(), 5);//将光标移动到合理位置 
		/*
		输入逻辑：
		如果输入对就继续输入，
		如果输入完当前行就下一行，
		如果按下ESC就退出
		如果输入错误就新增错误字符数，不继续输入
		*/

		char k = _getch();

		if (k == lines[lineIndex][inputIndex]) {
			input += k;
			inputIndex++;
			if (inputIndex == lines[lineIndex].size()) {
				lineIndex++;
				input = "";
				inputIndex = 0;
			}
		}
		// 是英文字符
		else 
		if ((k >= 'A' && k <= 'Z') || (k >= 'a' && k <= 'z') || 
			k=='.'||k=='!'||k=='?'||k=='\''||k==' ')
		{
				errorCount++;
		}
        else if (k == 27) {
			return ;
		}
        // 输入完
		if (lineIndex == lines.size()) {
			//等按键松开
			while (_kbhit()) {
				Sleep(30);// 防止占用过多CPU资源
            }
			IO << TUI::ClearScreen{} << TUI::GotoXY(15, 0) << "练习完成！总错误字符数： \033[4m" << errorCount << "\033[0m 字";
			IO << TUI::GotoXY(15, 2) ;
			system("pause");
			return;
		}
	}
}
int main() {
	std::vector<std::string> files = getFilesInDirectory("./text");
	std::vector<std::string> Show;
    for (size_t i = 0; i < files.size(); ++i) {
		size_t pos = files[i].find_last_of('\\');
		if (pos != std::string::npos) {
			Show.push_back(files[i].substr(pos + 1));
		}
		else {
			Show.push_back(files[i]);
		}
	}
	int fileIndex = 0;
	while (1) {
		IO << TUI::ClearScreen{} << TUI::GotoXY(15, 0) << "请选择要练习的文章：";
		IO << TUI::GotoXY(0, 2) << TUI::GotoXY(3, 1) << "上下箭头选择文章，回车确认";
			for (size_t i = 0; i < files.size(); ++i) {
			IO << TUI::GotoXY(4, i + 3) << i + 1 ;
			if (fileIndex == i) {
				 IO << ".\033[4m" << Show[i] << "\033[0m";
			}
			else {
				 IO << "." << Show[i];
			}
		}

		char k = _getch();
		if (k == 72)//上箭头
		{
			fileIndex--;
		}
		if (k == 80)//下箭头
		{
			fileIndex++;
		}
		// 先限制范围再进入练习界面，避免越界访问
		fileIndex = min(max(fileIndex, 0), static_cast<int>(files.size()) - 1);
		if (k == '\n' || k == '\r') 
		{
			pPractice(files[fileIndex], Show[fileIndex]);
		}

		
	}


	return 0x0;
}