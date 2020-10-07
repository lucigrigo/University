package com.tema1.goods;

import java.util.Map;

/**
 * Clasa care simbolizeaza un bun ilegal.
 */
public class IllegalGoods extends Goods {
    private final Map<Goods, Integer> illegalBonus;

    public IllegalGoods(final int id,
                        final int profit,
                        final int penalty,
                        final Map<Goods, Integer> illegalBonus) {
        super(id, GoodsType.Illegal, profit, penalty);

        this.illegalBonus = illegalBonus;
    }

    /**
     * @return bonusul unui bun ilegal
     */
    public Map<Goods, Integer> getIllegalBonus() {
        return illegalBonus;
    }
}
