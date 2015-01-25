UPDATE `creature_template` SET `InhabitType`= 4 WHERE `entry`= 40197;
DELETE FROM `conditions` WHERE `SourceEntry`= 75809;

REPLACE INTO `spell_script_names` (`spell_id`, `scriptname`) VALUES
(75809, 'spell_gb_shield_of_nightmares');
