//风云宴 玉贵人 苏妲己

#ifndef RULE_HPP
#define RULE_HPP
#include "Calculator.hpp"

/**
 * @brief
 *
 * @param rule
 * @param s
 * @return int : the optimal `full` value
 */
int banquetRule(BanquetRule *const &rule, States &s) {
    BanquetStrictRule
        *strictRule[NUM_CHEFS *
                    DISH_PER_CHEF]; // 下一阶段的规则，不受意图生效次数的影响
    BanquetLenientRule *lenientRule[NUM_CHEFS * DISH_PER_CHEF];
    for (int i = 0; i < NUM_CHEFS * DISH_PER_CHEF; i++) {
        strictRule[i] = &rule[i].strictRule;
        lenientRule[i] = &rule[i].lenientRule;
    }

    // 第1轮

    // 条件：三道炒：下阶段切技法料理售价+100%
    if (s.recipe[0]->cookAbility.stirfry > 0 &&
        s.recipe[1]->cookAbility.stirfry > 0 &&
        s.recipe[2]->cookAbility.stirfry > 0) {
        for (int i = 3; i < 6; i++) {
            if (s.recipe[i]->cookAbility.knife > 0) {
                strictRule[i]->addRule.buff += 100;
            }
        }
    }
    // 条件：三道烤：下阶段煮技法料理售价+100%
    if (s.recipe[0]->cookAbility.bake > 0 &&
        s.recipe[1]->cookAbility.bake > 0 &&
        s.recipe[2]->cookAbility.bake > 0) {
        for (int i = 3; i < 6; i++) {
            if (s.recipe[i]->cookAbility.boil > 0) {
                strictRule[i]->addRule.buff += 100;
            }
        }
    }
    // 条件：三道炸：下阶段蒸技法料理售价+100%
    if (s.recipe[0]->cookAbility.fry > 0 &&
        s.recipe[1]->cookAbility.fry > 0 &&
        s.recipe[2]->cookAbility.fry > 0) {
        for (int i = 3; i < 6; i++) {
            if (s.recipe[i]->cookAbility.steam > 0) {
                strictRule[i]->addRule.buff += 100;
            }
        }
    }
    // 条件：酸味: 本道料理基础售价+50%
    for (int i = 0; i < 3; i++) {
        if (s.recipe[i]->flavor.sour) {
            lenientRule[i]->baseRule.buff += 50;
            break;
        }
    }
    
    // 第2轮
    // 条件：五火：本道料理售价+50%
    for (int i = 3; i < 6; i++) {
        if (s.recipe[i]->rarity == 5) {
            lenientRule[i]->addRule.buff += 50;
            break;
        }
    }
    // 条件：酸味: 饱腹感-4
    for (int i = 3; i < 6; i++) {
        if (s.recipe[i]->flavor.sour) {
            lenientRule[i]->addRule.full += -4;
            break;
        }
    }
    // 条件：五火：本道料理意图+1
    for (int i = 3; i < 6; i++) {
        if (s.recipe[i]->rarity == 5) {
            lenientRule[i]->oneMore();
            break;
        }
    }
    // 条件：四火：下道料理意图+1
    for (int i = 3; i < 5; i++) {
        if (s.recipe[i]->rarity == 4) {
            lenientRule[i + 1]->oneMore();
            break;
        }
    }
    
    
    // 第3轮
    // 条件：蒸：本道料理售价-150%
    for (int i = 6; i < 9; i++) {
        if (s.recipe[i]->cookAbility.steam > 0) {
            lenientRule[i]->addRule.buff += -150;
            break;
        }
    }
    // 条件：煮：本道料理售价-150%
    for (int i = 6; i < 9; i++) {
        if (s.recipe[i]->cookAbility.boil > 0) {
            lenientRule[i]->addRule.buff += -150;
            break;
        }
    }
    // 条件：切：本道料理饱腹感-3
    for (int i = 6; i < 9; i++) {
        if (s.recipe[i]->cookAbility.knife > 0) {
            lenientRule[i]->addRule.full += -3;
            break;
        }
    }
    // 条件：一火：本道料理基础售价+50%
    for (int i = 6; i < 9; i++) {
        if (s.recipe[i]->rarity == 1) {
            lenientRule[i]->baseRule.buff += 50;
            break;
        }
    }
    return 19;//饱腹感
}
int banquetRule2(BanquetRule *const &rule, States &s) {
    BanquetStrictRule
        *strictRule[NUM_CHEFS *
                    DISH_PER_CHEF]; // 下一阶段的规则，不受意图生效次数的影响
    BanquetLenientRule *lenientRule[NUM_CHEFS * DISH_PER_CHEF];
    for (int i = 0; i < NUM_CHEFS * DISH_PER_CHEF; i++) {
        strictRule[i] = &rule[i].strictRule;
        lenientRule[i] = &rule[i].lenientRule;
    }
    // 第1轮

    // 条件：三道切：下阶段切技法料理售价+100%
    if (s.recipe[9]->cookAbility.knife > 0 &&
        s.recipe[10]->cookAbility.knife > 0 &&
        s.recipe[11]->cookAbility.knife > 0) {
        for (int i = 12; i < 15; i++) {
            if (s.recipe[i]->cookAbility.knife > 0) {
                strictRule[i]->addRule.buff += 100;
            }
        }
    }
    // 条件：三道煮：下阶段煮技法料理售价+100%
    if (s.recipe[9]->cookAbility.boil > 0 &&
        s.recipe[10]->cookAbility.boil > 0 &&
        s.recipe[11]->cookAbility.boil > 0) {
        for (int i = 12; i < 15; i++) {
            if (s.recipe[i]->cookAbility.boil > 0) {
                strictRule[i]->addRule.buff += 100;
            }
        }
    }
    // 条件：三道蒸：下阶段蒸技法料理售价+100%
    if (s.recipe[9]->cookAbility.steam > 0 &&
        s.recipe[10]->cookAbility.steam > 0 &&
        s.recipe[11]->cookAbility.steam > 0) {
        for (int i = 12; i < 15; i++) {
            if (s.recipe[i]->cookAbility.steam > 0) {
                strictRule[i]->addRule.buff += 100;
            }
        }
    }
    // 条件：苦味料理: 本道料理售价+100%
    for (int i = 9; i < 12; i++) {
        if (s.recipe[i]->flavor.bitter) {
            lenientRule[i]->addRule.buff += 100;
            break;
        }
    }
    
    // 第2轮
    // 条件：甜味料理: 饱腹感+3
    for (int i = 12; i < 15; i++) {
        if (s.recipe[i]->flavor.sweet) {
            lenientRule[i]->addRule.full += 3;
            break;
        }
    }
    // 条件：苦味料理：本道料理基础售价+50%
    for (int i = 12; i < 15; i++) {
        if (s.recipe[i]->flavor.bitter) {
            lenientRule[i]->baseRule.buff += 50;
            break;
        }
    }
    // 条件：第三道菜：第三道菜基础售价+200
    lenientRule[14]->baseRule.directAdd += 200;
    // 条件：五火：本道料理售价-100%
    for (int i = 12; i < 15; i++) {
        if (s.recipe[i]->rarity == 5) {
            lenientRule[i]->addRule.buff += -100;
            break;
        }
    }
    // 第3轮
    // 条件：苦味料理: 本道料理售价+100%
    for (int i = 15; i < 18; i++) {
        if (s.recipe[i]->flavor.bitter) {
            lenientRule[i]->addRule.buff += 100;
            break;
        }
    }
    // 条件：三火：本道料理饱腹感+2
    for (int i = 15; i < 18; i++) {
        if (s.recipe[i]->rarity == 3) {
            lenientRule[i]->addRule.full += 2;
            break;
        }
    }
    // 条件：炒：本道料理基础售价+50%
    for (int i = 15; i < 18; i++) {
        if (s.recipe[i]->cookAbility.stirfry > 0) {
            lenientRule[i]->baseRule.buff += 50;
            break;
        }
    }
    // 条件：第二道菜：第二道菜意图生效次数+1
    lenientRule[16]->oneMore();
    return 32;//饱腹感
}

#endif
