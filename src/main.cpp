#include <cstddef>
#include <pthread.h>
#include <stdio.h>

#define NUM_THREAD 4

// 각 스레드가 접근하려는 공유 자원
int shared = 0;

void *foo(void *arg) {
  // 각 스레드가 수행할 작업을 정의한 함수
  // -> 공유 자원에 10000번 접근하여 +1 증가시킴
  for (int i = 0; i < 10000; i++) {
    shared += 1;
  }
  return NULL;
}

int main() {
  // 4개의 스레드 생성
  pthread_t threads[NUM_THREAD];

  // foo 작업을 4개의 스레드로 동시에 실행 -> 공유 자원 shared 에 저장되는 값은
  // 40000 으로 예상
  for (int i = 0; i < NUM_THREAD; i++) {
    pthread_create(&threads[i], NULL, foo, NULL);
  }

  // 각 스레드 수행 종료 후 main thread 로 복귀
  for (int i = 0; i < NUM_THREAD; i++) {
    pthread_join(threads[i], NULL);
  }

  // 공유 자원에 저장된 결과값 출력
  printf("final results is %d\n", shared);

  return 0;
}
