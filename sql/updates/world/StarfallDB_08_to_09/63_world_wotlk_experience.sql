UPDATE `player_xp_for_level` SET `xp_for_next_level`= xp_for_next_level * 0.8 WHERE `lvl` BETWEEN 70 AND 79;
UPDATE `player_xp_for_level` SET `xp_for_next_level`= xp_for_next_level * 0.66 WHERE `lvl` BETWEEN 70 AND 79;
