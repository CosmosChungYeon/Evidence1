
# **큰 정수 연산 라이브러리**

## **1. 설치 방법**

### **Windows**
1. **MinGW** 설치  
   - 설치 후 `mingw32-make` 실행 환경 확인

2. **Clang 설치 (선택사항)**  
   - LLVM/Clang 설치 후 환경 변수에 경로 추가  

3. **필요한 도구**  
   - `gcc`, `clang`, `make`

---

### **macOS**
1. **Xcode Command Line Tools** 설치  
   ```bash
   xcode-select --install
   ```

2. **필요한 도구**  
   - `gcc`, `clang`, `make` (기본 포함)

---

### **Linux**
1. **GCC 및 Make 설치**  

   - **Ubuntu/Debian 계열**:  
     ```bash
     sudo apt-get update
     sudo apt-get install gcc make
     ```  
   - **Fedora/RHEL 계열**:  
     ```bash
     sudo dnf install gcc make
     ```

2. **Clang 설치 (선택사항)**  
   ```bash
   sudo apt-get install clang
   ```

---

## **2. 컴파일 및 실행 방법**

### **Windows**
1. **MinGW 또는 Clang**을 사용하여 컴파일
   ```bash
   mingw32-make
   ```
   Clang 사용 시
   ```bash
   mingw32-make CC=clang
   ```
2. **실행**  
   ```bash
   main.exe
   ```

---

### **macOS/Linux**
1. **Makefile을 사용하여 컴파일**  
   ```bash
   make
   ```
   Clang 사용 시
   ```bash
   make CC=clang
   ```

2. **실행**  
   ```bash
   ./main
   ```

---

## **3. 파일 구조**

```plaintext
프로젝트 폴더/
├── DH.c                # Diffie-Hellman 구현
├── test.c              # 테스트 코드
├── rand.c              # 난수 생성 함수
├── array_func.c        # 배열 관련 함수
├── calc_operations.c   # 계산 연산 함수
├── basic_func.c        # 기본 유틸리티 함수
├── main.c              # 메인 함수 (테스트 실행)
├── Makefile            # 빌드 설정 파일
└── README.md           # 프로젝트 설명 및 컴파일 방법
```

---

## **4. 테스트 방법**

### **Windows**  
```bash
main.exe
```

### **macOS/Linux**  
```bash
./main
```

---

## **5. 메모리 누수 확인**

### **Windows (Visual Studio 사용)**  
1. `_CrtSetDbgFlag`를 설정해 메모리 누수를 확인합니다.  
   ```c
   _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
   ```

2. 프로그램 실행 후 종료 시 메모리 누수를 확인합니다.

---

### **Linux/macOS (Valgrind 사용)**  
1. **Valgrind 설치**  
   ```bash
   sudo apt-get install valgrind
   ```

2. **메모리 누수 확인**  
   ```bash
   valgrind --leak-check=full ./main
   ```

---

## **6. GitHub 리포지토리**

자세한 소스 코드와 프로젝트 문서는 GitHub 리포지토리에서 확인할 수 있습니다.  

🔗 **[GitHub Repository](https://github.com/CosmosChungYeon/Evidence1)**  

---

## **7. 주요 기능**

- **기본 연산**: 덧셈, 뺄셈, 곱셈, 제곱, 나눗셈  
- **고급 연산**: Barrett Reduction, Karatsuba 곱셈 및 제곱  
- **모듈러 연산**: 모듈러 지수승  
- **활용 예시**: Diffie-Hellman 키 교환  