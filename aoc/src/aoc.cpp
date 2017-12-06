#include "stdafx.h"

struct problem {
	void solve() {
		prepare_input();
		precompute();
		std::cout << part_1() << std::endl;
		std::cout << part_2() << std::endl;
	}

	problem() = default;
	problem(const problem&) = default;
	problem(problem&&) = default;
	problem& operator=(const problem&) = default;
	problem& operator=(problem&&) = default;
	virtual ~problem() = default;


protected:
	[[gsl::suppress(f.6)]]
	virtual void prepare_input() {
	}

	[[gsl::suppress(f.6)]]
	virtual void precompute() {
	}

	[[gsl::suppress(f.6)]]
	virtual std::size_t part_1() {
		return 0;
	}

	[[gsl::suppress(f.6)]]
	virtual std::size_t part_2() {
		return 0;
	}
};

struct advent_1 : problem {
protected:
	std::string input = "77736991856689225253142335214746294932318813454849177823468674346512426482777696993348135287531487622845155339235443718798255411492778415157351753377959586612882455464736285648473397681163729345143319577258292849619491486748832944425643737899293811819448271546283914592546989275992844383947572926628695617661344293284789225493932487897149244685921644561896799491668147588536732985476538413354195246785378443492137893161362862587297219368699689318441563683292683855151652394244688119527728613756153348584975372656877565662527436152551476175644428333449297581939357656843784849965764796365272113837436618857363585783813291999774718355479485961244782148994281845717611589612672436243788252212252489833952785291284935439662751339273847424621193587955284885915987692812313251556836958571335334281322495251889724281863765636441971178795365413267178792118544937392522893132283573129821178591214594778712292228515169348771198167462495988252456944269678515277886142827218825358561772588377998394984947946121983115158951297156321289231481348126998584455974277123213413359859659339792627742476688827577318285573236187838749444212666293172899385531383551142896847178342163129883523694183388123567744916752899386265368245342587281521723872555392212596227684414269667696229995976182762587281829533181925696289733325513618571116199419759821597197636415243789757789129824537812428338192536462468554399548893532588928486825398895911533744671691387494516395641555683144968644717265849634943691721391779987198764147667349266877149238695714118982841721323853294642175381514347345237721288281254828745122878268792661867994785585131534136646954347165597315643658739688567246339618795777125767432162928257331951255792438831957359141651634491912746875748363394329848227391812251812842263277229514125426682179711184717737714178235995431465217547759282779499842892993556918977773236196185348965713241211365895519697294982523166196268941976859987925578945185217127344619169353395993198368185217391883839449331638641744279836858188235296951745922667612379649453277174224722894599153367373494255388826855322712652812127873536473277";

	size_t core(size_t offset) {
		size_t total = 0;
		const std::size_t end = input.size();
		for(size_t current = 0, next = offset; current != end; ++current, ++next) {
			if(next == end) {
				next = 0;
			}
			if(input[current] == input[next]) {
				total += input[current] - '0';
			}
		}
		return total;
	}

	std::size_t part_1() override {
		return core(1);
	}

	std::size_t part_2() override {
		return core(input.size() / 2);
	}
};

struct advent_2 : problem {
	using row = std::vector<std::size_t>;
	using spreadsheet = std::vector<row>;

protected:
	std::string input =
R"(1640	590	93	958	73	1263	1405	1363	737	712	1501	390	68	1554	959	79
4209	128	131	2379	2568	2784	2133	145	3618	1274	3875	158	1506	3455	1621	3799
206	1951	2502	2697	2997	74	76	78	1534	81	2775	2059	3026	77	2600	3067
373	1661	94	102	2219	1967	1856	417	1594	75	100	2251	2200	1825	1291	1021
57	72	51	1101	1303	60	1227	421	970	1058	138	333	1320	1302	402	1210
4833	5427	179	3934	4533	5124	4832	2088	94	200	199	1114	4151	1795	208	3036
759	876	110	79	1656	1691	185	544	616	312	757	1712	92	97	1513	1683
1250	1186	284	107	1190	1233	573	1181	1041	655	132	547	395	146	119	515
505	1726	79	180	86	1941	1597	1785	1608	1692	968	1177	94	184	91	31
1366	2053	1820	1570	70	506	53	415	717	1263	82	366	74	1255	2020	1985
2365	5585	2285	4424	5560	3188	3764	187	88	223	1544	5023	4013	5236	214	196
1487	1305	1359	1615	6579	2623	4591	150	5030	188	146	4458	5724	5828	1960	221
3114	688	3110	334	1921	153	4083	131	2234	3556	3573	3764	127	919	3293	104
1008	78	1196	607	135	1409	296	475	915	157	1419	1304	153	423	163	704
235	4935	4249	3316	1202	221	1835	380	249	1108	1922	5607	4255	238	211	3973
1738	207	179	137	226	907	1468	1341	1582	1430	851	213	393	1727	1389	632)";

	spreadsheet ss;

	void prepare_input() {
		//auto const ss = spreadsheet(
		//        input | ranges::view::split(is_char('\n'))
		//              | ranges::view::transform([](const std::string& line) -> row {
		//                return line | ranges::view::split(is_char('\t'))
		//                            | ranges::view::transform(ranges::convert_to<std::size_t>{});
		//                })
		//);

		std::vector<std::string> lines;
		boost::split(lines, input, [](char c) { return c == '\n'; });
		for(const std::string& line : lines) {
			std::vector<std::string> cells;
			boost::split(cells, line, [](char c) { return c == '\t'; });
			row r;
			std::transform(begin(cells), end(cells), std::back_inserter(r), [](const std::string& s) { return std::stoull(s); });
			ss.push_back(r);
		}
	}

	std::size_t part_1() {
		std::size_t running_checksum = 0;

		for(const row& r : ss) {
			const auto mm = std::minmax_element(begin(r), end(r));
			running_checksum += *mm.second - *mm.first;
		}
		return running_checksum;
	}

	std::size_t part_2() {
		std::size_t running_sum = 0;
		for(const row& r : ss) {
			const std::size_t end = r.size();
			for(size_t i = 0; i != end; ++i) {
				for(size_t j = 0; j != end; ++j) {
					if(i == j) {
						continue;
					}
					if(r[i] % r[j] == 0) {
						running_sum += r[i] / r[j];
					}
				}
			}
		}
		return running_sum;
	}
};

struct advent_3 : problem {
protected:
	std::ptrdiff_t input = 312'051;

	template<typename F>
	void spiral_iterate(F&& fn) noexcept {
		std::ptrdiff_t dx = 1;
		std::ptrdiff_t dy = 0;
		for(std::ptrdiff_t size = 1; ; ++size) {
			for(std::ptrdiff_t y = dy; y < dx; ++y) {
				if(!fn(dx, y)) {
					return;
				}
			}
			dy = dx;
			for(std::ptrdiff_t x = dx; x > -dx; --x) {
				if(!fn(x, dy)) {
					return;
				}
			}
			dx = -dx;
			for(std::ptrdiff_t y = dy; y > -dy; --y) {
				if(!fn(dx, y)) {
					return;
				}
			}
			dy = -dy;
			for(std::ptrdiff_t x = dx; x < -dx + 1; ++x) {
				if(!fn(x, dy)) {
					return;
				}
			}
			dx = -dx + 1;
		}
	}

	std::size_t part_1() override {
		// this is, of course, a silly way to solve this part, but it's the only way I can see to meaningfully share
		// the solution between parts 1 and parts 2. Badly designed question, IMO; the natural solution for the first
		// part is algebraic, rather than the brute force of the second part.

		std::ptrdiff_t current = 1;
		std::ptrdiff_t distance = 0;
		spiral_iterate([&](std::ptrdiff_t x, std::ptrdiff_t y) {
			if(++current == input) {
				distance = std::abs(x) + std::abs(y);
				return false;
			}
			return true;
		});
		return gsl::narrow<std::size_t>(distance);
	}

	using coordinate = std::pair<std::ptrdiff_t, std::ptrdiff_t>;

	struct coordinate_hash {
		std::size_t operator()(const coordinate& c) const noexcept {
			return std::hash<std::ptrdiff_t>{}(c.first) | std::hash<std::ptrdiff_t>{}(c.second);
		}
	};

	using visited_map = std::unordered_map<coordinate, std::ptrdiff_t, coordinate_hash>;

	std::ptrdiff_t sum_neighbours(const visited_map& visited, std::ptrdiff_t x, std::ptrdiff_t y) {
		const auto end = visited.end();
		auto it = visited.end();
		const std::ptrdiff_t sum = ((it = visited.find({ x - 1, y - 1 })) != end ? it->second : 0)
		                         + ((it = visited.find({ x - 1, y     })) != end ? it->second : 0)
		                         + ((it = visited.find({ x - 1, y + 1 })) != end ? it->second : 0)
		                         + ((it = visited.find({ x    , y - 1 })) != end ? it->second : 0)
		                         + ((it = visited.find({ x    , y + 1 })) != end ? it->second : 0)
		                         + ((it = visited.find({ x + 1, y - 1 })) != end ? it->second : 0)
		                         + ((it = visited.find({ x + 1, y     })) != end ? it->second : 0)
		                         + ((it = visited.find({ x + 1, y + 1 })) != end ? it->second : 0)
		;
		return sum;
	}

	std::size_t part_2() override {
		visited_map visited;
		visited[coordinate{ 0, 0 }] = 1;
		std::ptrdiff_t next_highest = 0;
		spiral_iterate([&](std::ptrdiff_t x, std::ptrdiff_t y) {
			std::ptrdiff_t value = sum_neighbours(visited, x, y);
			if(value > input) {
				next_highest = value;
				return false;
			}
			visited[coordinate{ x, y }] = value;
			return true;
		});
		return static_cast<std::size_t>(next_highest);
	}
};

struct advent_4 : problem {
protected:
	std::string passphrases =
std::string(R"(una bokpr ftz ryw nau yknf fguaczl anu
tvay wvco bcoblpt fwzg sfsys zvuqll mcbhwz ovcw fgdy
ynsocz vid rfmsy essqt fpbjvvq sldje qfpvjvb
yvh nxc kla vhy vkbq cxfzgr
kljv ymobo jlvk ebst cse cmlub tavputz omoby psif
ebfuvvu paqgzri uvvubef hglk jvn gzeln bdl ziqgpra bzcfa
tclq ytw tclq tezcqys
qae eofr yzwcwqf wqm ytcdnc pxnmkw
krryi irykr ycp lbeed ykrir lhq rdd tyujwd
hms pii lxoa dchsvz bepjwst bllxkqg hsm yrdj myzvju msh lwnnc
yxqh hqxy xkn ljjsqjh jjljshq
mhgsehj urbvnvf gbz ykxsd hsmgehj wtoc ujpfaos eir vifog tsy kdo
wfruf wwijme pxbbsvf asmgs ccbn vwtc mkhah oxxfh
lxqy jzvcvd cfgg uahxrwr dqmaqr bwzm wruxhra lrb lmk
jspgxo yuhgni njzqtn zglkzz ybc itj orqr zgqwuoo mjagh erll srqrk
cbrtnbx ukblei ienmdm sinzq lytyliz mma lizylty zeumwgu
aeggz eljcry buqdeog dvjzn ilvw arz vep kxdzm mvh szkf
imn sfty ugg flqq nydky mni bkqzlok wye lehwlmp xeyfmj
beyv oamrpkc tebdkwv zlq jes mqvif sej qpsnmjz edvtbkw
hylmacl wwlra xntnvg ppvb bzof cymllha
qktxomf ngfpuz qqz malc zxuqz szg zis vzro rfpgk
phru sxlg qzqlw uej vmd omzga jue
drzgojf ttqdqar weikik wvrjtxi gbj jramqh nlwoj drzgojf bgabmn xqlaeun
aiuohu pca apkmv cpa kmvpa nmdn
gelymv eto itcnuhn ote teo
oxiz xzio kqu wwgow
picoyb coibpy acsw ehlirq deyz gymqvz opicyb vuet lrl
zerg rezg miwtjgw gezr cui
mlh qlu ktil tnlgnrk bfqbk pgg qxeyd noadmjo nonlsh eqxdy
yqqaq yqqqa xod oss
mkotw bznvs xowoofq sebp wsgpsmn fytcpc vvmzr vmzrv xwtxz zrvvm
dvs twhz teqmlow oqg sjetxd aku cwl qfvrkex mndsio hfg
itdl qwdagkk wli tdil vlgur dyl xvfm
wlmyd dwmlx zhmqd zqmhd edzsvmz yclg umpq
petva gazw byrca pvaet epkoqh nlp vqfl vatpe
rykn ckr dijkme kmiedj ozlh deikmj
kuecjh sfqv pojfzf fjopzf fjpfzo amxtc
hri gglmial lrwbyc memgszu hir cfwlg ylcrwb
rxrfbtv pwpra fngt auh rapwp zrruuq uah
cevc utfd ysrfcw nnlg fnqtx aua htteunu mrjhhj
tvnxznj mvpagt nqmxvnl mutn ntmu eybh vkqeaj frayclp
ygktzxo lzwwy qsipu nwb jdmw pahao paow mwjd uivqbnj woap nyyogcc
log zihz rsmx ixfr xwvd osg zxc gol ufnbig
dogve cnb osa xbafl vefr nxlw yjgquui
ucyl aaoae ktjvi fyps xvjhpbh iiur tuc
pqt jasxg ehhs lzjzzzl sqmmj vwyva eklbtv hksanb fuesnd oyw fuesdn
uankv wesi frhpau qiucu lim uzbdapf ciwjd tifbqxh tfbtsdi
vgjd izpofu fqjpcct phuz
cfg cfg rgahl frm emn pbfsmgy frm jemwqgn sfpm azunntj igl
daps hpe fqg err sapd dci vbzlqx gsigq eyp rre
iuqyqdy djprdj mgtkdxr pwmkzv wmkvzp hppisd pidphs
rlr rrl vhevh cucprc xki urte lrr zfc xrqydzk ipjkyxj kytul
jwbkaee rgyjl rjljbwe ppq plp pfts ijd ckpvmw mbdrqh zolt lzmr
alw law awl wknavtb esklsbj wvssyai
aqy ldf qdht soxkg qtfipe nsdm aqe rtlc fbqrk ius gybbhxr
xteov wgqoqim nlz szlj oxevt xwb
tmgdst fyn oul tsohzbq ltmxji fgops gatssx zxdzfc talb
zkvjpu jnhtc nxs jqv pyoqz zsj ckwd xot ykai
fxfarre yjbxvj lqfaglo mbxuv bmuxv bxumv
yrhi uosldj hryi fwres ycygw ycvxze zevxyc iyk
yphev xisbai xdb hzrbg ayxbhdx qnvbus pwc
wytqraw yvurj erqckl rvrvda xsh gsd bxtm acxle gpndk
kpvjtu vacggk oabcuoq qusf zitqpgn pbyq ocabouq ntpgizq gaiiry dke
frz ceozajo ljltawq tjepzp iflv
zntejm dkfgc ysno noys sony muy
qdnyvvw oykq bnmldt zjgauw pviurd cbcnl tnkhq ebsey bccln arvwe
iqazt xidjgom wcrdz itht lfh ifzwkj rwqxhy ervcgmt vojg lzntz ezg
tlcxioh qvvkan wpi ody
mhsy dwm hyms yegvvc
hbkvi wvemc uwxgqf pwrgu wcy wxqfgu qkzppc vxcwdwd rcgp ivjd wmevc
upc ucp cpu unmr pyod
bqfew ebwfq paccwh phgc fchhr jrnio
abh bjalls bdtac zzvt totdlc yptqmgu rpcin bch cqklqly
bsnss qcsgi tegyz lqoqkpf qvatlyu ibza mzfotsk lye oqqf mnor
lzrxca stkbn axhr wckbip bsntk ahrx
oricdw cnpte dbz nqx xloxc bdz fdsl uyvgi nvoy ezbi
nlcqye ofta jcvqvtg yxduyh btawc tjgvqvc tcvqjvg
nji znctdfm kkmp pmt ikhl jjoubc xnp zdctnmf covvmsh ydh ircplcm
yafkuk yasqsyt ytqayss nusgb ukfyka
yogcf emg jlkd blupemf axg wihhrb ysernt yznhz
gmc yyqtgp use lohoit
lclwa ojjkm rxr rrx
punyfv iphw ddbc jghx lrssszc bepexv sicpy syicp lszrscs vrqjb
rjanra juh hljdmad scu usc baifu ijs suc bgdbbv
ogs hehi lgiwowc wwezznc ogs lorcl naunpll wlmal ajcbj ciujw
slenm xxod vhf amhts
mrrduda mrrduda lwecwjv lwecwjv vvzmjla cjipv
ixnv invx inmzz aoxghpv
ulyvfrf zsup zfryjy xoo agdsd giw papa ljtu rzbjiq wrex
bzpv svpuyov mklrct uzox
fxs iypd uaqch kxazj ksjyv
uxaommf xtq uubbfk bmlq kdhgjzg oxwpag itfij irmkjx ggod sddcyo bopn
lch plmvfni qbjr dnu zjcod qlwax gejmyj gxjqm mfzkb gejmyj
yoa thrfbto wposvrm amulogu mcqzfax fjquli oay
kywj kqqhney ozuljxz wqwfte ubo mjj anhhg aphy ocfnef yhin ywnx
vxuledm wllj obqtsrr jwll uvmelxd xvj gbwte
hevc bitwu ydw ywd btiwu iuether gfe
dzn ssmfpel wbbdeyt xge hrfi
zebz ifhq euto ppfnrwc winkkj
utuly wtdt iahpe ihtxwmh zxun bqluj hsaxgcs ytluu jlfnnuv drxlctr myhp
kwxgy hreul rsnh wdmsx kkajywb
bond djq kccazc zvzcie hndm myx cmhyhkc ove ord dqj
zcong tekgn pbzs ywqgqgu eizrx ypydeku yqyjdjp dwsu zxire zcgon iggnvf
tkioh hflkm fsjz gisjbi otikh
ccdqqm fdabbne fyd lbyqm cyzgtd puitvjz nluf hirrpxd tgxrg vvl
hjnygbz fnu twwbp xqw pfdlt uoalyme rsd muayeol ezcq
kubeooi bxgwoun paogjs twvwlji opsajg higbdfi aazo evmj
sfipxe mqbkmrn plwqd zvq nmvom fyfbs nbs qkrbmmn eym kqnrmbm
ruhsp hurps mqws umm sphru
ksjs pgpxh qozg enplxbn oqzg rvjnaje sjsk
rbwbvog mhgtgg uld twrqz rbf kpop
lwho lohw ylhd dej lydh vsfffsm
icljgu gluijc vthqx orynv xhvqt
biav elxkct mtaw nlafk snyr cbqdwim blim rtrqmc wze cxktel
fgpeia ebkhga azlfsr bsj pipvwsd nry bayrjzl ftth ynr mfhd
ymlowur nighqgk yjv pyxf nan xamb ohm jvy owrxbg icbz
iyyt linaqu httt zyfeo udap mllq pdxo lpl djhqaou zkit llp
dxspk yge kcqjqpz ulb hoe mfx nwayo
rdnmmh gyqd qhxrzj dgizu lyittbv txngpdg fiu mwd ndp oks vxnxybi
eul ztpe evnz yxx iuwon rkbbsw liy mqhxt
qahp zwn ualtk txbt cbthj xchqy pirucp povdwq
mqwu mwww muiafa miaafu hzripx wmww
auw hyyi ylewfi ihva jknbrry voxzooq xaos xymv qzzjw hjc
enpb jqa ajciy cbeopfs tqrlqj ecudb gso cyjai gxoet
yohkjj yohjjk xapawgo rtgnjj
lnlxxn nxllnx vhjrev uoew zts smkd kynlrg
bkblpr vgafcy alju aiyqe eebtsyu buve hdesodl pspbohw
aacmw qpndwo tcwsfqy qecnms wondpq sto
wdsyxe edsxyw jnzruiw pfqdrhi
pfgxekl vswgxhb qyn mykn jimiatq zkcz jimiatq kaexgxm mykn
xegwn upudt dew uqjrcl abyof hbtiko wxgne sorgno etm
xzojs zxsjo szjox gumjtwi
gttngkk bwdgce bhuw fgo rcbf byw
ngtzwqx ptx xodmy ctmtf oioahmm qajlhje jzilpk cvypp ijaefz
arlx slcugvm hyuo zoptsh emyr tndx rroecp tdnx xea rtkpd
sfckdx ktyrjju ruwjtp zhqznj vncun
oqqh xpc itrdg gtrid hoqq tuo yijh ncp suvck jic
brrlqu twdt urblrq twtd
brfuh arwtkpu mzlj wdyqk
pmag dtwnva nect azld axqrwy apgm xbv gdq ienubsy andvwt
hqb qbh gxdl mwjn cmfsmik
yiwma utlor qxjfjsn aomlvu gxp ryj rfkdsw kuguhyi qxxpg
ifq wcvcgly jdalgzx lgcycwv rajmnqw
latakk yxxbw evy vey
odkvw ojgveb jhg qwhkyoh btvu qbfot nouv owgtsi pdwbmfn pmvcv dnqbo
tmka qqnty knz swi fyvmt ikcdu jfjzsfu dshgi cosacuj szjjuff
eanet uua fbztk bzkft
jepi hyo jgzplr jyqk zzcs iepj hfamvu bfgbz sjsnf lprgzj
mlca ywko mtg vkfv ojka zbelq qkaujs simt kafq qtycfzo
sqh omv llvra ecvxmtx dpnafv llvszx xzlsvl quj ufnhvod faraf fivmnl
pvxlls fzeoav ahgv uhq nodcr cohy vqisgaj jsfcyur dbohh
ztccbwk okv vok kov ywel
xyu cmaikc jgqu ozccdzk ybn yoeq fky aetrkj eyoyvla laiu cermo
sssnb kxly mgvaz jpffkq bysbwwu rfnkm eycp ipyd hyi wjew
obdfqmh flkm semednj iafewg lvh uwa ciepe
zmldp ykffe gtehz qlmvule edrtzg prund oagwto qia bvyxur
kjok neno qbxh wqgkkt ympclso poyclsm cajgnnn
paqili kur sfit jbqchzx bhjqzxc
fhghm ubtaana qbn autnaab aaaunbt vmz
exlrl hfnpq zgdwx smix nyg ogccrhj iimhhwc uhcldo oydwxp kqc jxxpycv
wtdqjfh ialoqr zeej ipoh qtjdwhf wdhqftj
jcgug cmtvmu ynhnilj txlv uemowyu cvrool oolcvr njr cxqntdh
uhtwtp tgnc jmmjl utiu jfxtsoz cxwqcz
qntxl lyownp tsp tps mixyge rqfqumc bxjiry zmaj azjm
abt bat tftvm nyjs jyns
hzsdh pwthfvm cedg hzsdh rsxtehn owh cedg
hcoiny aqbeme eeuigt pocpvox tiugee rwb tvgmyc ojg hgdaf
mzlwcfc uoobo bouoo tvgvmiu evsfkm popgm evmfsk ehxvits vebxbmd qhmz jzj
mypgg jbpx vgeb ahvjl zbm ancdzfy wytkcq
bivscw zmzmjxu jzm fwb ujefxp jzsiskp cgx atcj sszikjp cxg nqvxga
vvurbxp iry zlz gfnlpuy npyugfl
fpmee mhj iul lui liu
xjoesn ggsdc vnisnmw kyxmmv xphfq
zcsml ngzlpy udaoab eotbv ylca bfmums izx
pdi bpyoep cofsy qazl oaovek fvfbe sotc lfdmaea smvs
zajm bskaqhj qxyiptb bdyeuqr dqjrekn iywj
hzhky hukvpve iqcbwju nyiwb rvutxlb hyuah urnhxg savicaw hexr ptedk
qndji wrr sin ljogf ncrb zvt tvz
kvfke tjpzhrl zvd doq kxyw fdgr oqd egkybdh rqpfxks nja
escstpv ccc ryzdv gxkjuyt gkhw jxnfda awpzg csestpv
cpcd onxeae nimbrpt zyji qnuo ktxgwbj vtjfglz skcozd zgii zgii nimbrpt
lwq iue hfbv hgbg aeqc
vzgbod yjkoc ckt bpiaz
eyco ecoy uzousjp faxj utu yoec
fhqdi myd tvex bzizkcx pifcfhz fczhpif eofzv bqzd knbhbgj dok ffcizhp
qlqlgmz hofmnc cwtk ahgnpne acn prwdh hwdrp rfofhl atavrf afkcbk
sgl apyfr pwxzptv osuwy vmqqh soyuw lqilked oinhh
eglqdox gcxfxql ejtnwu wvho can eyu uetwnj elgdxqo atvpkk eailsnn cwosyn
mylxhuj kbc apnllw qbmtj sqy hxtnvoe ins iyudo aagezrq nsi ikvn
lpmzo tkdeg zilkm vdkmtf yulbdd dkfmtv
fzrv grq zfvr ychga gqr
vdjxx wew pdxgp cjywsc meoffrj pgpdx chxmw eizgz ruea
iaklyhx btqqik tbiqqk ynmq laxykhi qatrnsh lnmtm plz
sfogup jtdsx tsxjd wwzkyy wzywky vgdsgr
paupqb kyy bccklmr vopviup lctcxza yyk yky
gduuia doek hqcr upvb szeewnu rrrdz
lhnsaf lut kzf allu dvj tyngx zkf aqsgz rtkzzdz
xxqj msg xxqj ezmm tmyji msg cco tain ctpel
pvcfzv rhn hlhxyu bghzzpx dlhvr hrvdl lhuxhy
npzhkp voghdv rvezqff hvgvdo jndf gpa wevrwpu
faixq aecax hxdouer yqlngzd grf wid iwd cce xnmmr
ifqwiah dib ibd dtvkwqj mpn dtwjkqv kyntq xwlv
rwoiz dja cvv lvza kfdblq bgtwgh ongdub wggthb lvaz
xajf eyasx rupsyqx wubjwx bsrqi ripghci sbzxp sbz dhooax
ydnv tvhwgp uvrh yryhl yxdlwa ladwxy awi mkwyn ghvpwt
qrl vwdvwic ocbhpi bcmz dor lrq hokg gokh
adz echnlju ebnmw twjl cfw loq fqklyyq clgqq jtgpsu wltj
vwlgisb murtsw ldkacqv wxfcke vcqkald ldhh gsl kpzn
itnvo lyddd saewfse spnri vtmst iblx
qsgv qni wvqiih mneg lkpb quhbkyi
efwaaa huu fslzwpc uuh szflwpc
sgmj ajh vcwpcua enltaks aquooh bwoda txbuve
vbe astgezx xqbxkdj evb bev yuuesdc fvohzq
gpn oqxfz pbwibjw gljdbf gbldfj sis dpk iss
pha ebybvye ntxhs wcuce
odnnywv qpcjll aslxqjm injfs vkbturz atxi
zzncfj kbhk jzzvnwf kqipx qkxpi rzb czfnzj
ygu vqpnxkw trdtv rrte
hrutley ljxuuq yonbpmk hmpc etyrhlu
odxp fpvizzx dxop jjbr skhxq mpzawhe zptdxuu erxk adbbuk zfzipvx
qjovasi yutjpg rcp bykpctm fqmmg pckbymt hqj
ssqc cype tkowxb fbh rsluu zjk scrukwv pkuexk qlgjtdq oulrke
bkcd nnf hdj sdlweyr uyf kmvzq
sgeg moy png blv bblree ufe uqknuqd lnjwbh
snpex hrbcfok pffv cwrvhcs fpk uprhn gbpy zkxyi esug ccnnj
bmwue dugcrdu uifiy clid rdmodec jodp hti xptj tpopl vuwhdyi hnoq
cwlkg qsz nnp lfyk pwn dpe oeuzp jusxxkq qlnchc
tsmkvge pxauyc cxypua boi hybq rzf iioyi rtedkc gjmk iob mqb
cvip wgbjhe ulwg jckkwd gdu bmaoisp
drpl xbliszf rpld ngnvgxl xnrd xsmd oetrcmn xvfohp mtocren
habmf dmfxq qitw xxtybla cxvb colcvpj sowoeuh bhmfa plccvjo naftjgw
cix soo icx ahx cdrjyxe htcnp
acoksaf cgahlg tdj euchwnj bdn lunouq aewrk uktre kklwqy lnouuq
ibsel hwjbah vxuk bjxa dvzbpq tffqvo bjax qfoftv
iynms tzv jakuuw cmz cjnyr ddibtd gcb
tmgerk pvwizc lxoma ergmtk xmg loaxm
ajazon yjwt viyemnk wobzwwm jcucn nopymyq znaajo qcjtmlq ccjun ywvt oqczod
kdhgnv kdnvgh rpyrxx xpyrxr
qftmshx hrbr kcggxw jwtuk qxbzkn
ddi fjekwxs xxua cmmkrso
ptrsv favvfh innnnx nninnx
kzsnd pnf evtazgw wmjk gvxp bslajo
nphqtka umlxu ymw whqiab whqiab vwigkz pevtps
vhje cnu uzfzum rwucy mxr wyrdqfi gnkuwz dkrwc otfc vbfc
ubtzio vlijsst anruj qyntadb fnic klz ywqq fnic vlijsst
rprj ybyqawb tgeieih nzcr rjpr bjfpozh tpevsx flvjdq
kvqqzvm cfdm wzjmkq sbcfx vzmkvqq
zqtt elpg eglp uoe glep
lqv madhtch xevl fal ijmx chcpra lzl afl cndbvnq
yjx jyx xjy otwklfj
cur egsdzaz ocbx wvky coxb pgiysbh lclhvy gfu oxbc vqyjvhh
gtd pytdaz kecsku nkiud ytt bmgobx tyt pfleji ebqlifv lqp ytzadp
bopfdvy eovszvw krgu jhuhyqi kaczafr krgu zlfxtl
yixprs zqai oprgw vcsjoc pgorw ypx ijo urjcjqv
estg oqnhw xgwajp mpbsag ibzi
zggbt jmmtkru sye ybd ztggb
tzryuqb blyxnnu sjpmf yxe zimf uyzqtbr qbyrtzu
rzivz rxn invxqd nazw efzun bwnw ywx rfuda jhnoww mketav
zxfw zcaqi qaciz ktefiwk xwzf
ntougl fvyaxfr obml obml bjkm lgsqj yfcggdu rqcpgt ntougl nveto
rma dakifg pvfc ticvff iffctv difkga
wpnt eclov vmmoqh qvw mljlvnj hxrx
ijnpo uhgxrfe xxopw xuzwyd powlpo ctduj eepw gubnepv
rxcmve myxckxk ecid nxe xevrmc juzaonr ilkx zpb pbz mvgos yzr
yfecm wqkh defqqa mnzgx nwe ixxg rjdhe new
awztgx vqgnfd iwcakr ajaiwn jiwnaa uqfrim wrgbjon ufqrmi vdu yjwy gwkdc
vrqf yzmvnr jkjji ghya pdlye ygha qlcm twmkex frqv
hjb xgypw vtr mgj asa owcuks fnllp ommrhng senv iix
usw iyuatv ondiwh neac ttge tzw bvjkfe neac usw
qwehwhj idrwo vex zopkjd lrcc sfqyz smte qrfh lccr qwjhewh vlb
efnlhsj ltm xirn nctwio cin
zocc cpfo czoc oiz tftk
rlzvqe inivone kptyumn eatw urjxc aetw
qavvqa jvvc yux cvvj
bfr fcpc xpkphcf irak bfr nuhsooj nniugf bfr gllq ipo
ekd dydxs rnmgb dek yowk
ipdll wdgx gjiigd uleiwg buvv vdhuzg gigidj gkyigmx lpdli lzyode fqdpvms
ycna rhyz bsipz lit rmc mrofb cyan mrc wujk
tjrk cwdsvf srkdjy lsyvryj nko syjvlry fgqq srdykj pgb koh dyle
sflcxt wmgdgej akllaoa bbsvve nsxnt nsxnt kgm akllaoa btqbez
bzmoci agemx mdtiol pyohvf zwtx aqblx oibmcz ypcmz lfg ckssn ozx
cuojke joekcu eusr dxqk xxwob klpsm
byspz lyunt eojrx ubh rjxoe ypzsb
ibok bkrtut wzcdk ppm qekhvy aupaic vswwul lmlxrv ainigy sasurbx
jeigcyc cycgjie resio ncz
xvxr lmlaje ebmtn cvms xrvx vsmc
cfjbffj xvo hpsbu nfm jhlsk mnf fmn
xncxo iwuon voj aebv jks nynzl hwjwo womejo ugzmr tdfaep olpdiaf
jlnusc hgpprf nulcjs kwiwypu kitjjbj snlcju
buqzm kpuoxel ajlqke qqdur jecuibn leajqk qudrq usi
ahbnjf uuzecdv yfyrsxv eoqey oonue vyyrxfs jixmvao
wjdi cfgurdl usdnlk jmao qnus cicxnux vtdxxkx nusq
mlvfz twu unj mar qpiz fhjczpz ytl npwjys ppq koa
ippdky pvwthzj qlkhl pvwthzj
kfm lcedomr xgdkrzo hfxyoe rafcby uwe pzjyuja weu nso erdwc fjvc
peep oufzlb fsgn kxj uge xvufb zsnrxss lere gfsn gvwajkj fmh
mexvi kgkktz kgkktz auyln ghvqc mexvi
wit qxtewrk qdaz oljeb wowb suergyt hxq pfnfbei rdu qrxkwte fyw
qjjzkd oxedeu uoxbehs zder vvjnn ocxkiz wkblzy eyzksc waiiqo fut raak
dhojys qkusuxs kzicui dcsxo
hsnexb yoz inza gqxtbc rya jqfe ufzlqva
scpquf gbloz ceol eclo qpvzavo rwfnxa
jyg edqf vdpsihl edqf
mbyjg yjgbm mgybj mhgi grw
ler oxssrel jhw jwh sfa hdhlo gng auzoan
hmkuis iaxf muhisk ikshum
eodbpo prajasi zsu hyb npr tbcntup uzs bxchne
zpyr kxmvz frlzwnb tzqrw vdh ndbwqmu cadwsv adq bzfnrwl qfgf
dybnn dmarc mknr fovokgj ukrp cuwag
khweq eljs rllijp pizevm lwws kehqw mkjcu otqodz
fvsrb kzbjbcc kzbjbcc mee dhyedb kzbjbcc
cnlmjd dvnd vhlvsa rsrtc scrrt tqhx vke jqmxpd udkjqc qxriw pfqpk
tyureg urteyg rutyge rmoihs
pccxeak tkmyane qqggpr tbdmpi ieb
wjucbi wjm hais pcxjd kkzh qns hmf mhf mnsv ifigsc
lqeyr pnopcig cpgoinp pncpigo mjfkjus cko zedvvyq
ofsnspv goj wqm ynolb qczly brl lrupzg buof zladwte
xzn zxn yaseulw qwhxb easyluw vvlmh
aiybip ydfczwh wkl rjsu xreokl qov mko pna fkfu
zjlwozs nxke ozwlzjs jybx jpsxp qtkll idsrad savpoe
xph lpvkmvy afq uqhg qqjgm smg tmhem mxdyqx bvhot lpvmkyv
jxkkzil pkjheow fewr ggbfy fuol cuzud wnx fxujfwh srjsmic
lzbjx vfx sncis xuv unoa nlgs stdhf oibxsgk uhogsb
hfqzkms bzyfnz npcd yhfdo myqukug pjq adle sqkfhmz
czhainb iazcnhb hhaqr cyrwj zzow luuvt zdyhnh uppysr
fyw dulbxa drewqsr tldlaac kyaw datclal ylplup hdzbj
kiiv tly gua lfg
gphbvwc lqdd jqja ffpkz hafal eiapksw wsikpea vphgbcw lkcpm zjxcx
viapp rxt vdgbm ezphp pcqr bll mklgx epzhp
favz bwmczgg zoyns pens wpgi mrwxel
ozwjjn kbzaozc cuaa igbfyq swi uypx bczaozk pyux odvawqx
npnpw nwppn egnpj fkzh wppnn
asu mlqmwa npewa cjluw qmalmw newpa fznx dzypi yiy
hleh usw bgmgscg cqc fijfuw idtyh cgmsbgg zjhr wus hymbju
tmre fvm cgowgb eduyfla ttez vdzp vtmtaog ezxsfi gyxgzi pvzd
acvarlu hkmfzdg jsnil hpv wjj rljpk pygl wjhhohk rkplj spvgx psgvx
wyz rvuobq kbmhaf bec bec
zosyz psuo lgihdo mjtftk fjkttm ddmcd
pqm qpswpb opviwxg ppqsbw waco jpx
yzgumgq kqv hqjghnl jixhoyg ufer kvq lzi rojm gbhvsd urd tuy
sxc jndqc ozpex wkchpu tmwv utcxzd piecpma cmppeia
ifjc lttj tltj rxmgxqa jcif lzhxkg zqb mdq kbjavv
isyxn zjbj uiw avziqxf zpezazx iuw
rjaudu amtpuk gufogys xiqs
gau sndrkv cmiolti cdxm ikkcisu xusnfbp jxffy ffcizj psye sgd
mvx onzmy oynzm mwfgvs
mrdg roanty dljs jlil gzcj dqitnfb gxb vzzqf ooweeh pgs oyntra
yna xgok fvbdl xgko udqp sorfo hmhl yan
kycl ule blupejp kycl fhpkoe pqkptw cfzpv nkncl
snugkyw zfdbsfs aehb olq kkoi xpsvy jqcspf lajjyu jtm
hifhfa mii clukcbc fhhifa wcts tgai vvqsyr kclcbcu
ordjftj dokk hdhytwc fjodrtj ojrjfdt san ajxrwy ked jfrqc
eylx cohd biswq xgiibz gzcptbf eylx icunv bfg jqanbv rntp sbfkiey
kub gdpbdms qnnto bit visqop
tywk clicj daics cbuewkx yyjjjka vxzk afsdyqg
)")
+
std::string(R"(bmxzll wqjnyr mxlzbl yutkaa qmpz hiqkf lqqqle jagj qlqelq
jgdeatg qubj jsu bhgbm swmgy lwgnuh qjbu dqwiikp mgwys
ryisldg asrrhz vxvrnk ibjr kebyx dwbx qdrpa tgakt
dfvgzk hifan dpjdnqc ncnvf xmqjjao npjq vobt evtaety kvufds pcugx oyjo
ezionjg ioznegj cykxy igeojzn ezm
dkv dkv vfqyl dkv dtjhrem
xfgh brsjcdw auvq fibb gcbecl
eet qdnrymr ndqmyrr tpfqxoi kbkxw
qhmaj maukf uygg hqmaj tfmtv irao wsari
ofoywus wxs leemkn wfko dwzqv txg qsiiiss aiiffe fadmdq zjtaovt
fgfms oazi sam msgff qif evxca reho
gpzhy qxh sco qeax wtabxwv sjd oev
xsmpi wskvku xspmi smipx
ghgf tbpeun qdivuvq dump umdp khxcxtx laljpv lownp egovve
vhmu eziabt hnz neko nkz hfmizn
vqhb lax zzyf lxa lik jrqynr rgcos
zjgbfzv ieufyz kjxad qxeuewx
ufl drkaac hoyic pqutop wqzdk eewabsr mqspcr ewarbse dzqkw
bgatanj xmddwv mwlmw scgzboo myignm lkfl fsqr
xkrx otjzfk wek dpbwk cromg fclmhg pkvw wsln
yyqjs lifg gifl cfv lfig fycza
dfup fkfeiqq rcmuv dly iforzi lngkjc rzifio oiifrz mlhor puwm qrthoa
nzfaeto punt rtmlg dwdk hyig
mds ueoyclh lxb axgea wqt wwqqglf tqw yvzji ryr dst bojf
ayoj yzj lyctgnc woxz gqltw lkzkwte wysb mjyeu hrwso
gymmvtt lhskza lsb nhlijnt men zphurrw oftksy zxs ykerwue hnijltn iknqyz
xuaxkc lgzeef fwb nlzzhjj lsieg qdr ews rue rdq
xnf lljcmod kyuercp kvlvd lkvh ncn afaq
bjytofa ltz mkyy bwt uxca somiz rhgdg keaqu ybr
aipljn qpq nilajp udgkchc dirvxg rrbmi mxfxkk kmfxkx
sfzjemk hjsvnmb hfd hprfmvg pbhkc
cvxi srj ucy yuc euswuns jpox
tajlnn ivuecv fdfce rakjq bfuxirh eibde tajnln nlajtn
ndvm mlnhy bfqlzn nmdv ohto
jysyvwy xbcyt lbbm osoye swwtwa emfznci qnzc qsgk
xcm jbqsuo xmc mtrk bojuqs
ukshrrh xhfl ooxgq vadlcrg ydva hugplg mnqbd wkyouq
mnmqys bhws megar krgoke modxe krgoke clovh dlo
ejl qzc agxph jcn zcq zqc
jgh yhh hjg jhg
tarm jboyg gbyjo pgalg xugzt bph mart
yur wrrahr fnnfqu rwhrar cdq
mukod gueg guge epalg xjkctt
hub hbu hbzul buh sqfl
xyrly lvpitr xfzn jjcl uvcnz dnpdyzq ifaiwe zlvzcx
wxzsf tgd khvwp cmd mzv bsvjvjm wvhpk ublnqyz mvbjvjs peishcb
zunmk hxpney nphxey znmku
bfxlgur wftcw xfkf fsik xkff ffxk
sxyjzr ugcscx uiovqx ldzhord xgxbfph ldzhord prdhg rhdhzd ugcscx
udg drb apyjq dgyevo fuxjhg
qshbe aigfdp wyvz xfcos wve dgfrufw dwimmb jfh wfrjbzk nwgrigr sbrpbb
ahpn xnzeof wxbv chxpcu jmso age ojsm bqonfki hqhrkw
mfupm vvig ndqbbm jlw
ejqh ebcrytj zpiqtpp ogznd
wkwkae odq rsrnqk nslczz hiyyhur kuw mjbuwll vduvod ryhuhiy swo tsos
znkufyx jejrdno knr wkx ikrlly tnxtj
iizdiw iizdiw hukep rwj eaq ptm klta rwj onaz
znb egqy qqnc igqr ikza ojgzkr xaen kurb pyckxvt wqx
pbohpw bphowp dajwdpp kotevs
hmuvxu zdnguk jhcmj gccyxiu cxgiycu uyxcgic akxi demeff
zjr lupzwcy puva rzj
cdn wee iqkbhl jwxo nhl cqd mqgqf ltdfg
phwco ggcj cggj ergpqmc kcz
aryjl wqwmkc aklktpz kptnroc mckqww
jadydt atjdyd tajdyd owswsgm
dshqt kacoge sdqth ylobih
kdnik knkdi dinkk xwvqa gvii
cifbkpt zye xhwnrhm fctibpk sbn pdqry emkye kzyjpa plzkc btkfcip gcchi
kekfr fufp dfy eqebgko obbn nuh
zixfbus skuf bea gimbqq caubhto eba uvkovz xisfzub peukmyn
okihcgh gazrc slee vlnwyg geviex eesl nmnvk rcbv ycupyw
tcvlgqs wxe lusvwzy unr yzluwvs wsylvzu zkwth qdykv
hyenkj ugao vlwgb putcepr lyeccs fqdotx burf aqew fje rfbu
uhmnc zgnkarz gylqawm abl zimcz qbs zzmic
pxkbpn zuxlwtt rlbhegv zlxuwtt ooxpr pgjx
leg wavgps fcplfpc xvxih ueskmi dvu wbiq nvtia pwjojw usiemk ojwwjp
zmrpknx xrfpq avque tvoyqp
lyposyj mckyoub sqbl olpsjyy hjafzi wmojb nvezofd
yflxrg egi aij qvc yflxrg typbs yflxrg kliexy eqnj jqrr
gggt sht kdajvz sht gkqwaot sht vout
ahl aucpih feig man umtchcv ceqabr tfptb
ftlywun voaorf kde ilwt hlpoe pksqxyh vpg cxo xgq fdkkl sgxhnq
zzekhfi akb lupta sgtd qapznzf lgidsx lidsgx akgmq ettuwjq xyumf
dxhpku lwoxpim gwb lhjmoh gxqapd ntmvc rvwwszg pvin lwoxpim coubc
qia bxmremo rjf vaeio eqexwz wuoz sguf bsbusof xqeewz
iczzz krf hbq tsgrih mzjabrt sfnwrm djignf zwac cwaz dgc nsrfmw
yvarsva zzpbp yai und kkbinr zlyj nyxxof ggrgu vyk eib
nepzm yrrgr vrlhbv hykmiog natrqx jvpq nbyhe zuo grx nwl
cfboeev hcn yfobyx cqvlo obctww xxaux ofybxy wouguq avuztl xmgqq xyofby
tikv uvzp oxopqy reh uzvp wefka vli kied gngks vbz thfsxyt
exxvknp pucbdyl dboto tzat qze xyinygz mhzl ubahr ekxbtk
jcz ufszbi pknsfgb ivok ijau okxolj etecn aurun zsa gbxs uryx
ypnb ousd osg mvset ipffzdn dfinfpz ltescx
taeoct aoetct aocett ttda fcdqnxv
bimtlk ssax bmrifkr vfxdmq hglp rgzr zpvk zhxtq rndwy mmr arkr
bwvdb axxbhzk nwfmbbu kzuc sahv cvas wdac acsv
xavkwou yvx ouwkxva otbe uzr mmw atq yiy ghavd qta pqlhv
omzht vsdsc zhtmo hmotz
eqt wtveez syift shtfnc hmckjxa apwbvn yme okdl hbihdtv hxahns eetvwz
rokdg ndjw hprxjc viys mbcctod dbvd
lhzb fyxf xaslmi sjd vqp grxhmfe snetfv mgivd uaknj givkdi
gxkxl kqcdnl rna jhcuepd npiedg djcpheu huce njryw bjluhq bvedvl kqxu
sogh uym atpzuwx vjgbe xgrvkg thgbyn mptcebt rkro
tnpxw uxrqxd lajmsmr tnnlt vrvbf deret hkmvrs eubvkn kks hjq
rcdoa zfja vod supip dvo
zbxdo xglqv how mgoq jqrdou pwrminc lidi nfs xglqv lidi
ldmnp dnqn ahhr tha mvsbsfh rpm rgus faf tjash
ewrdol jqhfpf rckj mrxlwj redjg bmxprx grla
rhr jksebwa vtu skwaejb vut
wrx iqvrjh atrt xrw vtqo tkcasd xedjh zkqrh vvhj
owc qlzygar uajwwe obzl inxawur
crbtrf phvy nzipo rctbfr trrcbf
vwuun wcfhhzo vxxjdt fbf bqtmmhs bffqcna
wkxfxmv zmrkyh sggw whwcw zukynw
lsdiy lnbn kblxi qfyib irfl mymrr zqbl
gwdkeu ghn afry zxoz fary uzntlnk kee xtnop ptnox zngoran
lgs lsg sgeseiz gsl
erpoqpi svtnv vsogl uym amzxbs
jtmodqx yjcsfcl zosugm jrekfdw xxbdqnx fcha
vio tlfxokx xaoq pydeiq glxsuzm honifvf maiuzsy uizsyam eco
ophcui saka qyt ltti syw
qff qff sde ryv
eiii jazx nlehtx tnhvxl rzvsjo qkupif feypppe tefxr wdjmlc
pdrr mwuy wccd rxla drpr enbbap
pclml ubwdbz hfudj gdpujfm ovabv
uink ffebi wdvhqzs qiympf lqxihty vnsp wdvhqzs hutxkcs lxfuos hutxkcs
fycoaw palkpz yrkg kappzl ncjym mergg kryg
eqy npvgh ghafkro piqnogb polacs qye hnvpg
dxyy udhmz jij tqsuic qxz erctv
urum nmbr cgek eetmhj gxr oxgukf wzdmvi oibzt fxkoug rcrywcr rglx
jkp ofej waibl opqhmww ifnczcg jdtkbc lil isc ill mylvuv
vqbcosk yhhsy gasmj bspx peakt cjtekw hvzo ywe qcvbosk ohzv qddt
edq llbvsx vedyvlm gou wkecank rkgf ziyrr belgo tbz
wbome vhzf ztk zaxiu ywjb supuf beq sxq spuuf pufus
femu ymkdoew kjynct aia
yjymr orovqj aremii licw bdtnc
uyade fbx duaye ujtvpn
yzvp pvzgjp yofcvya gvkkoh cafyvoy mhsm okhkvg
xuh qkaf dmi imd tzmlce mqkxj qilrc dim cadotvy
azpqgb kyc aflgyaf laagffy kesmk jzyzaer taf bpkbzdg
ogd dbdlh dqt zaaloh
exal vgnfx omu omepvwf szcwq snz bptite bzqyxl khmblyc sse emg
yqcbwsn aihhf tqck tcqk wqwqy cfez xahpn
qqbuf lil ies tqu pyxhqp mnfuk azj
vwma rzdtgl mxbasw nwgjav mwav
itpjfq rrgyt hralwm fqrig btwcod
ydjd kmk fvwr wrfv yvhw mkk
xbsxub yhsj xzbuf ace xubbsx fzuxb vxk
ttsist vubpf mhwkmtx vlj hdsva kmmhtwx ukxr upfvb tbma fxsrnxl hzwufho
wckjvz unmtev egxts ihw topvw ptowv rnihhmq
gpdtl kcric nwg ssbs qah aarp ydsdty ngw
lzhxbbq oktvcw xbasqe owtmwgp koa gumjie sodwrp hqsw aqh dtgsbb
xjbyy mxfxa ogvk nqiy qyni ldqwryj niyq jjixc
uhbul daccgva xtiz dim uhbul yjmakv yjmakv
huo esajup ouj oju ujo
eeeu hwvsk jfkmds okhi pogskfm itdlbll
lpyubo dylpfb iehwug decj ntidy cuygyg lalkb iutu oxgm imn)");

	std::vector<std::string> lines;

	void prepare_input() {
		boost::split(lines, passphrases, [](char c) { return c == '\n'; });
	}

	template<typename Fn>
	std::size_t core(Fn&& validate) {
		return gsl::narrow<std::size_t>(std::count_if(begin(lines), end(lines), [&](const std::string& line) {
			std::vector<std::string> words;
			boost::split(words, line, [](char c) { return c == ' '; });
			return validate(words);
		}));
	}

	std::size_t part_1() {
		return core([](std::vector<std::string>& words) {
			std::sort(begin(words), end(words));
			return end(words) == std::unique(begin(words), end(words));
		});
	}

	std::size_t part_2() {
		return core([](std::vector<std::string>& words) {
			for(std::string& word : words) {
				std::sort(begin(word), end(word));
			}
			std::sort(begin(words), end(words));
			return end(words) == std::unique(begin(words), end(words));
		});
	}
};

struct advent_5 : problem {
protected:
	std::string input =
R"(1
2
0
0
0
2
-2
-2
-3
-3
-7
0
-1
0
-10
-8
-12
-8
-3
-6
0
0
-18
-17
-11
-18
1
-7
-10
-4
-18
-8
-26
-15
-24
0
-8
-17
-15
-24
-7
-21
-15
-19
-30
-40
-44
-23
-3
-25
2
-31
-20
-45
-51
-50
-34
-4
-33
-41
0
-49
-43
0
-62
1
1
-32
-50
-22
-10
-60
-13
-46
-57
-40
-28
-33
-34
-13
-40
-5
-49
-17
-25
-71
-5
-16
-23
-58
-69
-22
-28
-84
-70
-71
-73
-87
-8
-11
-99
-65
-27
-32
-48
-87
-96
1
-58
-101
-94
2
-52
-34
-22
2
-25
-7
-36
-66
-84
-100
-45
-65
-69
-52
-5
-4
-93
-100
-7
-13
-50
-87
-87
-4
-119
-25
1
-41
-58
-24
-12
-15
-39
-140
-40
-136
-88
-141
-112
-43
-68
-67
-128
-23
-24
-90
-56
-71
-146
-46
-41
-76
-54
-38
-144
-53
-1
-97
0
0
-70
-60
-171
-12
-97
-147
-21
-174
-108
-101
-91
-56
-76
-13
-177
-1
-40
-2
-177
-136
-168
-126
-5
-175
-177
-144
-104
-174
-4
-172
-114
-69
-18
-24
-157
-47
-110
-6
-155
-79
-157
-93
-93
-114
-77
-148
-32
-100
-192
-144
-123
-192
-65
-220
-143
-1
-40
-149
-69
-230
-202
-69
-52
-112
-175
-72
-69
-168
-198
-181
-156
-37
-179
-168
-81
-51
-205
-2
-104
-25
-199
-83
-176
-115
-174
-204
-207
-127
-161
-219
-27
-107
-160
-141
-34
-39
-182
-46
-41
-90
-267
-234
-48
-72
-49
-110
-266
-167
-194
-124
-183
-184
-108
-49
-130
-166
-198
-87
-196
-183
-275
-130
-275
-39
-70
-143
-257
-22
-53
-12
-93
-30
-141
-32
-239
-284
-186
-211
-160
-145
-21
-167
-258
-67
-56
-262
-272
-19
-194
-244
-95
-261
-27
-109
-271
-7
-146
-328
-266
-207
-76
-204
-273
-177
-159
-68
-231
-215
-75
-264
-27
-342
-298
-338
-178
-268
-303
-78
-283
-149
-147
-209
-146
-147
-282
-131
-204
-129
-319
-166
-256
-114
-267
-211
-15
-194
-53
-114
-236
-127
-33
-316
-123
-180
-234
-131
-107
-21
-209
-174
-174
-24
-1
-281
-367
-251
-42
-17
-158
-33
-181
-26
-286
-235
-262
-1
-374
-121
-253
-215
-19
-114
-8
-372
-89
-185
-50
-71
-130
-248
-274
-9
-99
-66
-402
-256
-294
-313
-256
-36
-229
-64
-47
-32
-259
-178
-278
-416
-334
-286
-229
-377
-50
-424
-359
-182
-41
-270
-96
-372
-1
-100
-45
-88
-111
-373
-247
-185
-356
-66
-246
-157
-326
-196
-258
-325
-218
-43
-224
-429
-461
-159
-101
-21
-187
-416
-154
-416
-311
-54
-189
-379
-375
-300
0
-405
-170
-478
-119
-451
-121
-30
-304
-320
-218
-369
-294
-41
-328
-482
-42
-200
-254
-409
-260
-447
-196
-156
-394
-142
-180
-376
-316
-323
-455
-262
-360
-143
-318
-242
-226
-382
-211
-493
-443
-14
-231
-304
-168
-396
-100
-201
-187
-209
-49
-45
-150
-309
-275
-449
-523
-260
-366
-222
-483
-234
-209
-398
-247
-343
-266
-456
-396
-528
-232
-241
-482
-417
-362
-406
-503
-164
-146
-198
-285
-23
-133
-506
-159
-203
-70
-35
-410
-209
-482
-304
-45
-550
-27
-6
-117
-121
-143
-265
-196
-179
-334
-77
-253
-526
-276
-437
-212
-276
-253
-414
-192
-48
-53
-28
-24
-139
-554
-534
-82
-35
-237
-447
-274
-125
-377
-404
-101
-241
-166
-192
-120
-469
-461
-534
-222
-409
-363
-211
-477
-300
-491
-506
-512
-344
-554
-31
-617
-49
-268
-63
-143
-512
-115
-299
-344
-453
-573
-590
-330
-342
-347
-3
-46
-344
-423
-561
-411
-95
-9
-323
-354
-523
-523
-526
-573
-162
-281
-578
-326
-475
-506
-319
-190
-15
-193
-586
-430
-166
-72
-160
-530
-233
-626
-345
-253
-413
-152
-217
-672
-675
-498
-417
-104
-25
-114
-283
-187
-314
-51
-88
-217
-311
-408
-148
-420
-615
-221
-454
-461
-213
-131
-115
-326
-244
-561
-133
-50
-434
-544
-616
-418
-302
-366
-202
-624
-302
-241
-158
-494
-321
-555
-136
-601
-363
-246
-630
-705
-121
-427
-91
-453
-664
-271
-210
-155
-573
-232
-349
-152
-208
-233
-395
-185
-121
-291
-149
-11
-263
-55
-488
-78
-155
-447
-667
-556
-730
-406
-454
-382
-496
-568
-235
-374
-200
-475
-513
-275
-423
-95
-643
-434
-144
-527
-418
-577
-564
-211
-485
-122
-387
-484
-212
-129
-763
-268
-83
-428
-518
-394
-784
-223
-549
-232
-175
-566
-569
-329
-300
-3
-563
-571
-369
-753
-111
-609
-461
-514
-514
-174
-800
-702
-808
-780
-708
-774
-811
-518
-741
-404
-364
-48
-74
-228
-333
-380
-90
-813
-457
-275
-414
-281
-723
-101
-123
-438
-657
-406
-779
-161
-825
-715
-79
-358
-183
-554
-716
-596
-56
-39
-505
-268
-425
-609
-69
-92
-7
-44
-10
-681
-86
-30
-225
-551
-213
-335
-829
-817
-804
-74
-109
-732
-781
-401
-370
-40
-526
-694
-336
-859
-294
-682
-264
-325
-27
-679
-135
-82
-711
-570
-159
-179
-604
-41
-580
-403
-540
-262
-69
-329
-5
-879
-345
-632
-367
-183
-38
-80
-63
-448
-832
-656
-774
-292
-474
-596
-862
-842
-16
-107
-243
-647
-782
-336
-785
-816
-78
-416
-712
-810
-389
-264
-304
-847
-520
-619
-161
1
-584
-719
-486
-516
-360
-747
-363
-672
-134
-177
-894
-778
-582
-766
-769
-114
-843
-287
-493
-30
-620
-467
-141
-206
-437
-367
-426
-799
-943
-508
-594
-545
-61
-829
-844
-589
-775
-409
-28
-726
-452
-261
-613
-106
-441
-496
-643
-606
-742
-408
-321
-260
-333
-328
-751
-21
-768
-36
-265
-936
-697
-702
-924
-89
-215
-896
-216
-477)";

	std::vector<std::ptrdiff_t> instructions;

	void prepare_input() override {
		std::vector<std::string> lines;
		boost::split(lines, input, [](char c) { return c == '\n'; });
		std::transform(std::begin(lines), std::end(lines), std::back_inserter(instructions), [](const std::string& line) {
			return std::stoll(line);
		});
	}

	std::size_t part_1() override {
		std::vector<std::ptrdiff_t> my_instructions(instructions);
		std::size_t instruction_count = 0;
		for(auto it = std::begin(my_instructions); it != std::end(my_instructions);) {
			const std::ptrdiff_t jump = *it;
			*it += 1;
			it += jump;
			++instruction_count;
		}
		return instruction_count;
	}

	std::size_t part_2() override {
		std::vector<std::ptrdiff_t> my_instructions(instructions);
		std::size_t instruction_count = 0;
		for(auto it = std::begin(my_instructions); it != std::end(my_instructions);) {
			const std::ptrdiff_t jump = *it;
			if(jump >= 3) {
				*it -= 1;
			} else {
				*it += 1;
			}
			it += jump;
			++instruction_count;
		}
		return instruction_count;
	}
};

struct advent_6 : problem {
	std::string input = "14	0	15	12	11	11	3	5	1	6	8	4	9	1	8	4";
	
	using memory_type = std::vector<std::size_t>;

	memory_type memory;

	void prepare_input() override {
		std::vector<std::string> elements;
		boost::split(elements, input, [](char c) { return c == '\t'; });
		std::transform(std::begin(elements), std::end(elements), std::back_inserter(memory), [](const std::string& element) {
			return std::stoull(element);
		});
	}

	std::size_t rebalance_iterations = 0;
	std::size_t cycle_length = 0;

	void precompute() override {
		memory_type my_memory(memory);
		std::vector<memory_type> previous_configurations;
		for(;;) {
			++rebalance_iterations;
			auto highest = std::max_element(std::begin(my_memory), std::end(my_memory));
			std::size_t blocks = *highest;
			*highest = 0;
			for(auto it = ++highest; blocks != 0; ++it) {
				if(it == std::end(my_memory)) {
					it = std::begin(my_memory);
				}
				*it += 1;
				--blocks;
			}
			if(auto it = std::find(std::begin(previous_configurations), std::end(previous_configurations), my_memory); it != previous_configurations.end()) {
				cycle_length = gsl::narrow<std::size_t>(std::distance(it, std::end(previous_configurations)));
				break;
			} else {
				previous_configurations.push_back(my_memory);
			}
		}
	}

	std::size_t part_1() noexcept override {
		return rebalance_iterations;
	}

	std::size_t part_2() noexcept override {
		return cycle_length;
	}
};

int main() {
	advent_1 a1;
	a1.solve();

	advent_2 a2;
	a2.solve();

	advent_3 a3;
	a3.solve();

	advent_4 a4;
	a4.solve();

	advent_5 a5;
	a5.solve();

	advent_6 a6;
	a6.solve();

	return 0;
}
