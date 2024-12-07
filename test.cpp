#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

// ANSI 이스케이프 코드
#define CLEAR_SCREEN "\033[2J"    // 화면 전체 지우기
#define CURSOR_HOME "\033[H"      // 커서를 화면 맨 위로 이동
#define CURSOR_HIDE "\033[?25l"   // 커서 숨기기
#define CURSOR_SHOW "\033[?25h"   // 커서 보이기

void renderChatroom(const std::vector<std::string>& messages) {
    // 화면 초기화
    std::cout << CLEAR_SCREEN << CURSOR_HOME;

    // 상단 고정 메시지 출력
    std::cout << "============================\n";
    std::cout << "         Chatroom          \n";
    std::cout << "============================\n";

    // 채팅 메시지 출력
    for (const std::string& msg : messages) {
        std::cout << msg << "\n";
    }

    // 입력 영역 안내
    std::cout << "\nType your message ('exit' to quit): ";
    std::cout.flush();
}

int main() {
    std::vector<std::string> messages;
    std::string input;

    // 커서 숨기기
    std::cout << CURSOR_HIDE;

    // 채팅 루프
    while (true) {
        // 화면 렌더링
        renderChatroom(messages);

        // 사용자 입력
        std::getline(std::cin, input);

        // 종료 조건
        if (input == "exit") {
            break;
        }

        // 메시지 추가
        messages.push_back("You: " + input);

        // 메시지 수 제한 (스크롤 효과)
        if (messages.size() > 20) { // 최대 20줄 유지
            messages.erase(messages.begin());
        }
    }

    // 커서 복구
    std::cout << CURSOR_SHOW;

    return 0;
}
