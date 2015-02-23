-- Halfus
UPDATE `creature_template` SET `mechanic_immune_mask`= 617299967 WHERE `entry` IN (44600, 46209, 46210, 46211);
-- TaV
UPDATE `creature_template` SET `DamageModifier`= 60, `mechanic_immune_mask`= 617299967 | 33554432 | 256 WHERE `entry` IN (45992, 45993, 49897, 49898, 49899, 49903, 49904, 49905);

REPLACE INTO `spell_script_names` (`spell_id`, `scriptname`) VALUES
(83644, 'spell_lct_summon_mystic_traps'),
(91252, 'spell_lct_summon_mystic_traps');
