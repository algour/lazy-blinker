/*
 * Copyright 2017 Alexander Gorodetsky alexander@gorodetsky.org
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define F_CPU 1200000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define Bit(bit)  (1<<(bit))

#define ClearBit(reg, bit)       reg &= (~(1<<(bit)))

#define SetBit(reg, bit)          reg |= (1<<(bit))

#define BitIsClear(reg, bit)    ((reg & (1<<(bit))) == 0)

#define BitIsSet(reg, bit)       ((reg & (1<<(bit))) != 0)

#define InvBit(reg, bit)	  reg ^= (1<<(bit))

unsigned int i;

// Инициализация портов
void initAll()
{
	cli(); //Запрет прерываний на время выполнения иницилизации

	// пины на выход
	DDRB |= (1 << PB3)|(1<<PB4);     //Базы транзисторов подключены к выводам 2 (PB3) и 3 (PB4)

	// пины на вход
	DDRB &= ~((1 << PB0)|(1 << PB1));    //Переключатель поворотников подключен к выводам 5 (PB0) and 6 (PB1)

	//включаем подтяжку к питанию (высокий уровень) (pull-up resistor)
	PORTB |= (1 << PB0)|(1 << PB1);

	//Включение прерываний на выводах PCINT0..5
	GIMSK = GIMSK|(1<<PCIE);

	//Настройка конкретных выводов для прерываний
	PCMSK = (1<<PCINT0)|(1<<PCINT1);

	sei(); //Разрешение прерываний

}


/*
 * Функция задержки с отслеживанием состояния переключателя поворотников
 */
void delay(int pin) {
	for (i=0;i<=180;i++) {
		if (!(PINB & _BV(pin))) {
			break;
		}
		_delay_ms(200);
	}
}

/*
 * Функция чтения состояния вывода
 * с простым антидребезгом
 * Return 1 - на опрашиваемом выводе 0, 0 - на выводе не 0.
 */
int isLow(int pin) {
	unsigned int first_check;
	unsigned int second_check;

	first_check = (PINB & _BV(pin));
	_delay_ms(10);
	second_check = (PINB & _BV(pin));

	return !(first_check || second_check || 0);

	//для проверки высокого состояния (чтобы не забыть)
	//return (first_check & second_check & 1);
}

int main()
{
	initAll();
	while (1) {
		//нечего делать
    	}
}

ISR(PCINT0_vect) //Прерывание на PCINT
{
	//проверка переключателя SW1
	if (isLow(PB0)) {
		ClearBit(PORTB,4); 	// Выключаем поворотник SW2
		SetBit(PORTB,3); 	// Включаем поворотник SW1
		delay(PB1);		// Удерживаем поворотник включенным, но проверям не включился ли соседний
		ClearBit(PORTB,3); 	// Выключаем поворотник SW1
	}

	//проверка переключателя SW2
	if (isLow(PB1)) { // is low?
		ClearBit(PORTB,3); 	// Выключаем поворотник SW1
		SetBit(PORTB,4); 	// Включаем поворотник SW2
		delay(PB0); 		// Удерживаем поворотник включенным, но проверям не включился ли соседний
		ClearBit(PORTB,4); 	// Выключаем поворотник SW2
	}

}

