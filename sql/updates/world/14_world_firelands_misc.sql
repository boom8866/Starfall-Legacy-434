
/*
15:03:22.321 -- first text
15:03:33.413 -- second text
15:03:44.005 -- 3rd text

15:07:51.001 -- nun gut.


15:13:18.931 -- aggro

15:13:21.536 -- die macht des m. --> skorpion

15:13:21.318 scoprion form


15:13:22.207 -- so every 700 - 800 ms
15:13:23.018
15:13:23.720

15:15:18.927 -- cat form
 
15:15:36.321 -- leaping flames summon 17 secs
15:15:51.999 -- next 16 secs
15:16:04.121 -- next 12 secs

15:15:36.321 -- leaping flames cast
15:15:51.999
*/

UPDATE `gameobject_template` SET `flags`= 4 WHERE `entry`= 209277;
DELETE FROM `creature_template_addon` WHERE `entry`= 52571;
UPDATE `creature_template` SET `scriptname`= 'boss_majordomo_staghelm', `dynamicflags`= 0 WHERE `entry`= 52571;
UPDATE `creature_template` SET `scriptname`= 'boss_baleroc' WHERE `entry`= 53494;

DELETE FROM `creature_text` WHERE `entry`IN (52571, 53494);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(52571, 0, 0, 'Well well... I admire your tenacity. Baleroc stood guard over this keep for a thousand mortal lifetimes.', 14, 0, 100, 0, 0, 24473, 'Majordomus Hirschhaupt'),
(52571, 1, 0, 'But NONE may enter the Firelord\'s abode!', 14, 0, 100, 0, 0, 24474, 'Majordomus Hirschhaupt'),
(52571, 2, 0, 'Beg for mercy now, and I may yet allow you to live. Well, \"heroes\", what is your answer?', 14, 0, 100, 0, 0, 24475, 'Majordomus Hirschhaupt'),
(52571, 3, 0, 'Very well. Witness the raw power of my new lord!', 14, 0, 100, 0, 0, 24464, 'Majordomus Hirschhaupt'),
(52571, 4, 0, 'The master\'s power takes on many forms…', 14, 0, 100, 0, 0, 24483, 'Majordomus Hirschhaupt'),
(52571, 4, 1, 'Behold the rage of the Firelands!', 14, 0, 100, 0, 0, 24485, 'Majordomus Hirschhaupt'),
(52571, 5, 0, '|TInterface\\Icons\\inv_mount_hordescorpiong.blp:20|t%s transforms into a |c0087CEFA|Hspell:98379|h[Scorpion]|h|r!', 41, 0, 100, 0, 0, 0, 'Majordomus Hirschhaupt'),
(52571, 6, 0, '|TInterface\\Icons\\ability_druid_tigersroar.blp:20|t%s transforms into a |c0087CEFA|Hspell:98374|h[Cat]|h|r!', 41, 0, 100, 0, 0, 0, 'Majordomus Hirschhaupt'),
(52571, 7, 0, 'Burn.', 14, 0, 100, 0, 0, 24477, 'Majordomus Hirschhaupt'),
(52571, 7, 1, 'Soon, ALL of Azeroth will burn!', 14, 0, 100, 0, 0, 24479, 'Majordomus Hirschhaupt'),
(52571, 7, 2, 'You stood in the fire!', 14, 0, 100, 0, 0, 24481, 'Majordomus Hirschhaupt'),
(52571, 8, 0, 'Nothing but ash!', 14, 0, 100, 0, 0, 24478, 'Majordomus Hirschhaupt'),
(52571, 9, 0, '|c00FF0000%s summons Burning Orbs!|r', 41, 0, 100, 0, 0, 0, 'Majordomus Hirschhaupt'),
(52571, 10, 0, 'Blaze of Glory!', 14, 0, 100, 0, 0, 24472, 'Majordomus Hirschhaupt'),
(52571, 11, 0, '|c00FF0000Burning Seeds are growing!|r', 41, 0, 100, 0, 0, 24472, 'Majordomus Hirschhaupt'),
(52571, 12, 0, 'My studies… had only just begun…', 14, 0, 100, 0, 0, 24471, 'Majordomus Hirschhaupt'),

(53494, 0, 0, 'You are forbidden from my master\'s domain, mortals.', 14, 0, 100, 0, 0, 24441, 'Baloroc'),
(53494, 1, 0, 'Fool mortals. Hurl yourselves into your own demise!', 14, 0, 100, 0, 0, 24446, 'Baloroc'),
(53494, 2, 0, 'Burn beneath my molten fury!', 14, 0, 100, 0, 0, 24459, 'Baloroc'),
(53494, 3, 0, 'By the Firelord\'s command, you, too, shall perish!', 14, 0, 100, 0, 0, 24447, 'Baloroc'),
(53494, 4, 0, '|TInterface\\Icons\\spell_shadow_curse.blp:20|t%s readies his |cFF7A0080|Hspell:99352|h''Decimation Blade''|h|r bereit!', 41, 0, 100, 0, 0, 0, 'Baloroc'),
(53494, 5, 0, '|TInterface\\Icons\\inv_sword_09.blp:20|t%s readies his |cFFFF0000|Hspell:99350|h''Inferno Blade''|h|r bereit!', 41, 0, 100, 0, 0, 0, 'Baloroc'),
(53494, 6, 0, 'You have been judged.', 14, 0, 100, 0, 0, 24449, 'Baloroc'),
(53494, 6, 1, 'Behold your weakness.', 14, 0, 100, 0, 0, 24451, 'Baloroc'),
(53494, 6, 2, 'None shall pass!', 14, 0, 100, 0, 0, 24452, 'Baloroc'),
(53494, 7, 0, 'Mortal filth... the master\'s keep is forbidden...', 14, 0, 100, 0, 0, 24444, 'Baloroc'),
(53494, 8, 0, 'Your flesh is forfeit to the fires of this realm.', 14, 0, 100, 0, 0, 24450, 'Baloroc');
