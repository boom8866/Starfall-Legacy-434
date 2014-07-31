REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(42188, 0, 0, 'None may pass into the World\'s Heart!', 14, 0, 100, 0, 0, 21919, 'Ozruk - Aggro'),
(42188, 1, 0, '|TInterface\\Icons\\ability_warrior_shieldreflection.blp:20|tOzruk casts |cFFFF0000|Hspell:78939|h[Elementium Bulwark]|h|r!', 41, 0, 100, 0, 0, 0, 'Ozruk - Announce Elementium Bulwark'),
(42188, 2, 0, 'Break yourselves upon my body. Feel the strength of the earth!', 14, 0, 100, 0, 0, 21921, 'Ozruk - Shield Buff'),
(42188, 3, 0, '%s becomes enraged!', 41, 0, 100, 0, 0, 0, 'Ozruk - Enrage'),
(42188, 4, 0, 'The cycle is complete.', 14, 0, 100, 0, 0, 21920, 'Ozruk - Slay'),
(42188, 5, 0, 'A protector has fallen. The World\'s Heart lies exposed!', 14, 0, 100, 0, 0, 21922, 'Ozruk - Death');

UPDATE `creature_template` SET `minlevel`= 84, `maxlevel`= 84, `scriptname`= 'boss_ozruk' WHERE `entry`= 42188;
UPDATE `creature_template` SET `minlevel`= 87, `maxlevel`= 87, `faction_A`= 14, `faction_H`= 14, `exp`= 3, `VehicleId`= 867 WHERE `entry`= 49654;

UPDATE `creature_template` SET `minlevel`= 88, `maxlevel`= 88, `faction_A`= 14, `faction_H`= 14, `scriptname`= 'npc_tsc_rupture' WHERE `entry`= 49576;
UPDATE `creature_template` SET  `scriptname`= 'npc_tsc_rupture_controller' WHERE `entry`= 49597;
UPDATE `creature_model_info` SET `bounding_radius`= 0.75, `combat_reach`= 0.75 WHERE `modelid`= 36550;

REPLACE INTO `creature_onkill_reward` (`creature_id`, `RewOnKillRepFaction1`, `MaxStanding1`, `RewOnKillRepValue1`, `CurrencyId1`, `CurrencyCount1`) VALUES
(49654, 0, 0, 0, 395, 70); -- 5 players heroic
