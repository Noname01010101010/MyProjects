//Реализоватьприложение "Жонглер" Параметры работы жонглера: N - количество мячей T
//- время жонглирования в минутах. По истечении этого времени новые мячи не подбрасываются.
//Приложение ожидает падения всех мячей. 1.
//основной поток "подбрасывает" (запускает в отдельных потоках)
//N мячиков с интервалом в одну секунду отслеживает упавшие мячи и подбрасывает
//их повторно каждый мячик должен иметь уникальный идентификатор, сохраняемый на все время работы жонглера
//перед каждым "броском" выводится информация о мячах: количество мячей в полете, количество мячей в руках,
//идентификаторы всех мячей с их состоянием 2. каждый подброшенный мяч "летит" в отдельном потоке время "полета"
//у каждого мячадолжно быть случайным в интерфвале от 5 до 10 секунд (определяется при броске) каждую секунду
//мяч должен выводить информацию: идентификатор мяча, <сколько секунд прошло>/<сколько секунд должен лететь мяч>

package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

type Ball struct {
	id       int
	duration int
}

var (
	idCounter = 0
	flying    = make(map[int]Ball)
	holding   = make(map[int]Ball)
	fallChan  = make(chan Ball)
	mu        sync.Mutex
	wg        sync.WaitGroup
)

func ballFly(b Ball) {
	ticker := time.NewTicker(time.Second)
	defer ticker.Stop()
	defer wg.Done()

	for i := 1; i <= b.duration; i++ {
		fmt.Printf("Мяч #%d: %d/%d секунд в полёте\n", b.id, i, b.duration)
		<-ticker.C
	}

	fmt.Printf("[УПАЛ] Мяч #%d упал\n", b.id)
	fallChan <- b
}

func throwBall(ball Ball) {
	if ball.id == 0 {
		idCounter++
		ball.id = idCounter
		ball.duration = rand.Intn(6) + 5 
	}

	fmt.Printf("[ПОДБРОС] Мяч #%d подброшен на %d секунд\n", ball.id, ball.duration)
	flying[ball.id] = ball
	wg.Add(1)
	go ballFly(ball)
}

func juggler(N int, T int) {
	stopTime := time.Now().Add(time.Duration(T) * time.Minute)
	loopTicker := time.NewTicker(time.Second)
	defer loopTicker.Stop()

	
	for i := 0; i < N; i++ {
		mu.Lock()
		throwBall(Ball{})
		mu.Unlock()
		time.Sleep(time.Second)
	}

	
	go func() {
		for b := range fallChan {
			mu.Lock()
			delete(flying, b.id)
			holding[b.id] = b
			mu.Unlock()
		}
	}()

	stopReThrowing := false
	for {
		<-loopTicker.C

		mu.Lock()
		if time.Now().After(stopTime) {
			stopReThrowing = true
		}

		fmt.Printf("\n[СТАТУС] В полёте: %d | В руках: %d\n", len(flying), len(holding))
		for _, b := range flying {
			fmt.Printf("- Мяч #%d: летит\n", b.id)
		}
		for _, b := range holding {
			fmt.Printf("- Мяч #%d: в руках\n", b.id)
		}

		if !stopReThrowing {
			for id, b := range holding {
				delete(holding, id)
				fmt.Printf("[ПОВТОРНО] Мяч #%d снова подброшен\n", b.id)
				throwBall(b)
				time.Sleep(time.Second)
			}
		} else if len(flying) == 0 && len(holding) > 0 {
			// Завершаем, если все мячи упали, и они в руках
			mu.Unlock()
			break
		}
		mu.Unlock()
	}

	fmt.Println("[ОЖИДАНИЕ] Ожидаем падения всех мячей...")
	wg.Wait()
	close(fallChan)
	fmt.Println("[ГОТОВО] Все мячи упали.")
}

func main() {
	rand.Seed(time.Now().UnixNano())
	juggler(3, 1) 
}
