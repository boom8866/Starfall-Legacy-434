UPDATE `creature_template` SET `faction_A`= 16, `faction_H`= 16 WHERE `entry`= 48936;
UPDATE `creature_template` SET `flags_extra`= 130 WHERE `entry`= 48974;
DELETE FROM `creature_template_addon` WHERE `entry` IN (48974, 48975, 49039, 49040, 48976, 49041, 49042);
UPDATE `creature_template` SET `unit_flags`= unit_flags | 256 | 512, `InhabitType`= 4 WHERE `entry` IN (48975, 48976, 49039, 49040, 49041, 49042, 48974);

REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(47162, 0, 0, 'Glubtok show you da power of de arcane!', 14, 0, 100, 0, 0, 21151, 'Glubtok - Aggro'),
(47162, 2, 0, 'Fists of flame!', 14, 0, 100, 0, 0, 21153, 'Glubtok - Fists of Flame'),
(47162, 1, 0, 'Fists of frost!', 14, 0, 100, 0, 0, 21156, 'Glubtok - Fists of Frost'),
(47162, 3, 0, 'Glubtok ready?', 14, 0, 100, 1, 0, 21154, 'Glubtok - Phase Intro 1'),
(47162, 4, 0, 'Let\'s do it!', 14, 0, 100, 15, 0, 21157, 'Glubtok - Phase Intro 2'),
(47162, 5, 0, 'ARCANE POWER!!!', 14, 0, 100, 15, 0, 21146, 'Glubtok - Phase Intro 3'),
(47162, 6, 0, '|TInterface\\Icons\\spell_holy_innerfire.blp:20|t %s creates a moving |cFFFF0000|Hspell:91398|h[Fire Wall]|h|r!', 41, 0, 100, 0, 0, 0, 'Glubtok - Announce Firewall'),
(47162, 7, 0, 'Hahahaha!', 14, 0, 100, 0, 0, 21152, 'Glubtok - Slay 1'),
(47162, 7, 1, 'Blowed that one!', 14, 0, 100, 0, 0, 21155, 'Glubtok - Slay 2'),
(47162, 8, 0, 'TOO...MUCH...POWER!!!', 14, 0, 100, 15, 0, 21145, 'Glubtok - Death');
