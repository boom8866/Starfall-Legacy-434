UPDATE `instance_template` SET `script`= 'instance_well_of_eternity'  WHERE `map`= 939;

UPDATE `creature_template` SET `scriptname`= 'boss_perotharn' WHERE `entry`= 55085;
UPDATE `creature_template` SET `scriptname`= 'npc_legion_demon_intro' WHERE `entry`= 55503;
UPDATE `creature_template` SET `scriptname`= 'npc_legion_demon' WHERE `entry`= 54500;

UPDATE `creature_template` SET `scriptname`= 'npc_woe_illidan' WHERE `entry`= 55500;


DELETE FROM `areatrigger_scripts` WHERE `entry` IN (7029, 7066);
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(7029, 'at_woe_intro'),
(7066, 'at_woe_illidan_intro');

REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(55085, 1, 0, 'Er ist nah und verbirgt sich in den Schatten... Ich kann es spüren.', 12, 0, 100, 0, 0, 26118, 'Peroth\'arn'),
(55085, 2, 0, 'Du da, Teufelswache. Schütze diesen Bereich.', 12, 0, 100, 0, 0, 26120, 'Peroth\'arn'),
(55085, 3, 0, 'Ihr anderen sichert den Innenhof.', 12, 0, 100, 0, 0, 26121, 'Peroth\'arn'),

(55500, 1, 0, 'Hier drüben, in den Schatten.', 12, 0, 100, 0, 0, 26076, 'Illidan Sturmgrimm'),
(55500, 2, 0, 'Ich glaube, wir haben eine bessere Chance, wenn wir gemeinsam kämpfen.', 12, 0, 100, 0, 0, 26525, 'Illidan Sturmgrimm'),
(55500, 3, 0, 'Wir verstecken uns in den Schatten, verborgen vor unseren Feinden.', 12, 0, 100, 0, 0, 26054, 'Illidan Sturmgrimm'),
(55500, 4, 0, 'Kommt mit mir, falls ihr lang genug leben wollt, um zu sehen, wie ich die Welt rette!', 12, 0, 100, 0, 0, 26065, 'Illidan Sturmgrimm'),
(55500, 5, 0, 'So viele Dämonen und keine Zeit.', 12, 0, 100, 0, 0, 26066, 'Illidan Sturmgrimm'),
(55500, 6, 0, 'Ich werde sie aufhalten, so dass wir vorbei können. Haltet Euch bereit.', 12, 0, 100, 0, 0, 26063, 'Illidan Sturmgrimm'),
(55500, 7, 0, 'Meine Magie lässt nach. Ich gehe hindurch!', 12, 0, 100, 0, 0, 26064, 'Illidan Sturmgrimm to Illidan Sturmgrimm'),
(55500, 8, 0, 'Tod der Legion!', 12, 0, 100, 0, 0, 26056, 'Illidan Sturmgrimm to Schreckenslordverteidiger'),
(55500, 9, 0, 'Zerschlagt den Kristall. Wir müssen weiter.', 12, 0, 100, 0, 0, 26104, 'Illidan Sturmgrimm'),
(55500, 10, 0, 'Wir gehen. Bleibt dicht bei mir.', 12, 0, 100, 0, 0, 26055, 'Illidan Sturmgrimm'),
(55500, 11, 0, 'Sie strömen ohne Unterlass aus dem Palast.', 12, 0, 100, 0, 0, 26069, 'Illidan Sturmgrimm'),
(55500, 12, 0, 'Zerstört den Energiefokus des Portals.', 12, 0, 100, 0, 0, 26105, 'Illidan Sturmgrimm'),
(55500, 13, 0, 'Der Gestank von Pech und Schwefel... Diese Portale sind genauso verderbt wie die Dämonen selbst.', 12, 0, 100, 0, 0, 26037, 'Illidan Sturmgrimm'),
(55500, 14, 0, 'Tod der Legion!', 12, 0, 100, 0, 0, 26056, 'Illidan Sturmgrimm'),
(55500, 15, 0, 'Lasst uns dieses letzte Portal schließen und die Sache beenden.', 12, 0, 100, 0, 0, 26072, 'Illidan Sturmgrimm'),
(55500, 16, 0, 'Sie ahnen nicht, dass ihr Tod nur Augenblicke entfernt ist.', 12, 0, 100, 0, 0, 26101, 'Illidan Sturmgrimm'),
(55500, 17, 0, 'Tod der Legion!', 12, 0, 100, 0, 0, 26056, 'Illidan Sturmgrimm to Verderbter Arkanist'),
(55500, 18, 0, 'Die Dämonen dürften alle verschwinden. Wir werden im Handumdrehen am Palast sein.', 12, 0, 100, 0, 0, 26073, 'Illidan Sturmgrimm'),
(55500, 19, 0, 'Die Dämonen strömen nicht länger aus dem Palast. Wir können weiter.', 12, 0, 100, 0, 0, 26074, 'Illidan Sturmgrimm'),
(55500, 20, 0, 'Zu einfach.', 12, 0, 100, 0, 0, 26075, 'Illidan Sturmgrimm'),
(55500, 21, 0, 'Noch ein Dämon, der darauf wartet, vernichtet zu werden.', 12, 0, 100, 0, 0, 26050, 'Illidan Sturmgrimm'),
(55500, 22, 0, 'Nichts wird mich aufhalten. Noch nicht einmal du, Dämon.', 12, 0, 100, 0, 0, 26049, 'Illidan Sturmgrimm'),
(55500, 23, 0, 'Eure Magie ist lächerlich. Ich zeige Euch meine.', 12, 0, 100, 0, 0, 26053, 'Illidan Sturmgrimm to Peroth\'arn'),
(55500, 24, 0, 'Zurück in die Schatten!', 12, 0, 100, 0, 0, 26048, 'Illidan Sturmgrimm'),
(55500, 25, 0, 'Meine Kraft kehrt zurück.', 12, 0, 100, 0, 0, 26102, 'Illidan Sturmgrimm to Illidan Sturmgrimm'),
(55500, 26, 0, 'Aus dem Jäger ist der Gejagte geworden.', 12, 0, 100, 0, 0, 26051, 'Illidan Sturmgrimm to Peroth\'arn'),
(55500, 27, 0, 'Gute Arbeit, doch für den Moment muss ich allein weiter. Gute Jagd.', 12, 0, 100, 0, 0, 26052, 'Illidan Sturmgrimm');
