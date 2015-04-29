DELETE FROM `spell_bonus_data` WHERE `entry` = '25742';
INSERT INTO `spell_bonus_data` (`entry`, `comments`) VALUES
(25742, 'Paladin - Seal of Righteousness');

UPDATE `spell_bonus_data` SET `direct_bonus`=0, `ap_bonus`=0 WHERE `entry` IN (25742, 20167);