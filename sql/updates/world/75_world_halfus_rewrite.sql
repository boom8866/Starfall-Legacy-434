DELETE FROM `creature` WHERE `id` IN (44765, 44797, 44641, 44650, 44652, 44645, 44687);

UPDATE `creature_template` SET `scriptname`= 'boss_halfus_wyrmbreaker' WHERE `entry`= 44600;
UPDATE `creature_template` SET `unit_flags`= 33554432 WHERE `entry`= 44765;

REPLACE INTO `spell_script_names` (`spell_id`, `scriptname`) VALUES
(83487, 'spell_bot_chain'),
(83611, 'spell_bot_dragon_debuffs'),
(84092, 'spell_bot_dragon_debuffs'),
(83601, 'spell_bot_dragon_debuffs'),
(83603, 'spell_bot_dragon_debuffs'),
(86058, 'spell_bot_fireball'),
(83719, 'spell_bot_fireball');


DELETE FROM `creature_text` WHERE `entry`= 44600;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(44600, 0, 0, 'Cho''gall will have your heads! ALL OF THEM!', 14, 0, 100, 0, 0, 20186, 'Halfus Wyrmbreaker - Aggro'),
(44600, 1, 0, 'The wyrms will eat well tonight!', 14, 0, 100, 0, 0, 20187, 'Halfus Wyrmbreaker - Slay 1'),
(44600, 1, 1, 'The burden of the damned falls upon you!', 14, 0, 100, 0, 0, 20188, 'Halfus Wyrmbreaker - Slay 2'),
(44600, 2, 0, '%s binds the $n to his will!', 41, 0, 100, 0, 0, 0, 'Halfus Wyrmbreaker - Bind to Will'),
(44600, 3, 0, '%s roars furiously!', 41, 0, 100, 0, 0, 0, 'Halfus Wyrmbreaker - Furious Roar');

UPDATE `creature_template` SET `InhabitType`= 1, `baseattacktime`= 2000 WHERE `entry` IN (44765, 44797, 44641, 44650, 44652, 44645);
