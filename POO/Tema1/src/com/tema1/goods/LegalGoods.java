package com.tema1.goods;

/**
 * Clasa care simbolizeaza un bun legal.
 */
public class LegalGoods extends Goods {
    private final int kingBonus;
    private final int queenBonus;

    public LegalGoods(final int id,
                      final int profit,
                      final int penalty,
                      final int kingBonus,
                      final int queenBonus) {
        super(id, GoodsType.Legal, profit, penalty);

        this.kingBonus = kingBonus;
        this.queenBonus = queenBonus;
    }

    /**
     * @return bonusul de king pentru un bun anume
     */
    public int getKingBonus() {
        return kingBonus;
    }

    /**
     * @return bonusul de queen pentru un bun anume
     */
    public int getQueenBonus() {
        return queenBonus;
    }
}
