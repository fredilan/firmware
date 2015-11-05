#include "ActuatorInterfaces.h"
#include "ActuatorPwm.h"
#include "Ticks.h"
#include "ActuatorMutexDriver.h"

ActuatorPwm::ActuatorPwm(ActuatorDigital* _target, uint16_t _period) :
    ActuatorDriver(_target) {
    periodStartTime = ticks.millis();
    periodLate = 0;
    dutyLate = 0;
    value = 0.0;
    minVal = 0.0;
    maxVal = 100.0;
    target->setActive(false);
    setPeriod(_period);
    recalculate();
}

void ActuatorPwm::recalculate() {
    temp_long_t newDutyTime = temp_long_t(value)
            * (temp_long_t(period_ms) / temp_long_t(100));
    temp_long_t correctionFactor = temp_long_t(period_ms + periodLate)
            / temp_long_t(period_ms);
    dutyTime = int32_t(newDutyTime * correctionFactor);
}

void ActuatorPwm::setValue(temp_t const& val) {
    temp_t val_(val);
    if (val_ <= minVal) {
        val_ = minVal;
    }
    if (val_ >= maxVal) {
        val_ = maxVal;
    }

    if (value != val_) {
        temp_t delta = val_ - value;
        value = val_;
        recalculate();
        if(delta > temp_t(5.0)){
            // big positive change, go high immediately by starting a new period
            dutyLate = 0;
            periodLate = 0;
            periodStartTime = ticks.millis() - period_ms;
        }
        else if(delta < temp_t(-5.0)){
            // big negative change, go to low part of period immediately
            periodStartTime = ticks.millis() - dutyTime + dutyLate;
        }
    }
}

void ActuatorPwm::update() {
    target->update();
    int32_t adjDutyTime = dutyTime - dutyLate;
    int32_t currentTime = ticks.millis();
    int32_t elapsedTime = currentTime - periodStartTime;

    if (target->isActive()) {
        if (elapsedTime >= adjDutyTime) {
            // end of duty cycle
            target->setActive(false);
            // check if turning the output off has succeeded (OnOff actuator could stay active due to time limit)
            if (target->isActive()) {
                return; // try next time
            }
            dutyLate += elapsedTime - dutyTime;
        }
    }
    if (!target->isActive()) { // <- do not replace with else if
        if (elapsedTime >= period_ms) {
            // end of PWM cycle
            if (adjDutyTime < 0) {
                // skip going high for 1 period when previous periods built up
                // more than one entire duty cycle (duty is ahead)
                // subtract duty cycle form duty late accumulator
                dutyLate = dutyLate - dutyTime;
            } else {
                if(dutyTime > 0){
                    if(target->type() == ACTUATOR_TOGGLE_MUTEX){
                        static_cast<ActuatorMutexDriver*>(target)->setActive(true, priority());
                    }
                    else{
                        target->setActive(true);
                    }
                    if (!target->isActive()) {
                        return; // try next time
                    }
                }
            }
            periodLate = elapsedTime - period_ms;
            // limit to half of the period
            periodLate = (periodLate < period_ms / 2) ? periodLate : period_ms / 2;
            // adjust next duty time to account for longer period due to infrequent updates
            // low period was longer, increase high period (duty cycle) with same ratio
            recalculate();
            periodStartTime = currentTime;
        }
    }
}

int8_t ActuatorPwm::priority(){
    int32_t adjDutyTime = dutyTime - dutyLate;
    int32_t priority = (adjDutyTime*100)/period_ms;
    if(priority > 127){
        priority = 127;
    }
    if(priority < 0){
        priority = 0;
    }
    return priority;
}
