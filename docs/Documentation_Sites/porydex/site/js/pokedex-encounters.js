/* Porydex Encounters panels (Lucid-style, file:// friendly)
 * Provides:
 *  - PokedexEncountersMainPanel (list of locations + encounter table)
 *  - PokedexEncountersPanel     (detail panel; reused by router for /encounters/:location)
 *
 * Assumes globals exist: Panels, _, Dex, toID, BattleLocationdex, BattlePokedex, BattleSearch, BattleLocationIdMap (we build it), etc.
 */

// Map from toID(location display name) -> key in BattleLocationdex
var BattleLocationIdMap = {};
if (typeof BattleLocationdex !== 'undefined') {
    for (var locKey in BattleLocationdex) {
        if (!BattleLocationdex.hasOwnProperty(locKey)) continue;
        if (locKey === 'rates') continue;
        var loc = BattleLocationdex[locKey] || {};
        var name = loc.name || locKey;
        var nameId = toID(name);
        if (!nameId) continue;
        // first wins; avoids weird duplicates
        if (!(nameId in BattleLocationIdMap)) BattleLocationIdMap[nameId] = locKey;
    }
}

function cleanLocationName(name) {
    name = String(name || '');
    // Drop time-of-day suffixes
    name = name.replace(/\s*-\s*(Morning|Day|Night|Evening|Dawn|Dusk)\s*$/i, '');
    // Strip the "Unused Ruby Sapphire Map X" noise
    name = name.replace(/\s*-\s*Unused\s+Ruby\s+Sapphire\s+Map\s*\d+\s*/ig, '');
    // Common cosmetic trims
    name = name.replace(/\s*-\s*Corridors?\b/ig, ''); // "Hidden Floor Corridors" -> "Hidden Floor"
    name = name.replace(/\s+/g, ' ').trim();
    // Normalize title casing lightly (keep existing case if already good)
    // Keep exact wording but fix "Of" casing often seen in generated names
    name = name.replace(/\bOf\b/g, 'of');
    return name;
}

// Hide the trailing " 0" (map index) when it is the only map for that base location.
// Example: "Littleroot Town 0" -> "Littleroot Town".
function stripTrailingZeroIfSingle(cleanName, baseCounts) {
    var m = String(cleanName || '').match(/^(.*)\s0$/);
    if (!m) return cleanName;
    var base = (m[1] || '').trim();
    if (!base) return cleanName;
    // Only strip when this base appears exactly once.
    if (baseCounts && baseCounts[base] === 1) return base;
    return cleanName;
}


// Internal links must work on file:// (no pushState). Hash links are safe everywhere.
function dexLink(path) {
    if (!path) return '#';
    if (path.charAt(0) === '/') path = path.slice(1);
    return '#' + path;
}

function getLocationKeyFromIdOrName(locationIdOrName) {
    var id = toID(locationIdOrName || '');
    if (!id) return null;
    if (typeof BattleLocationdex !== 'undefined' && BattleLocationdex[id]) return id; // already a key
    if (BattleLocationIdMap[id]) return BattleLocationIdMap[id];
    // fallback: try direct match on cleaned names
    if (typeof BattleLocationdex !== 'undefined') {
        for (var k in BattleLocationdex) {
            if (!BattleLocationdex.hasOwnProperty(k) || k === 'rates') continue;
            var loc = BattleLocationdex[k] || {};
            var nm = loc.name || k;
            if (toID(cleanLocationName(nm)) === id) return k;
        }
    }
    return null;
}

function escape(s) { return Dex && Dex.escapeHTML ? Dex.escapeHTML(String(s || '')) : _.escape(String(s || '')); }

function pokemonIconHTML(speciesId) {
    try {
        if (Dex && Dex.getPokemonIcon) {
            var sp = Dex.species && Dex.species.get ? Dex.species.get(speciesId) : null;
            var out = Dex.getPokemonIcon(sp || speciesId);

            // Some builds return a full <span ...>...</span>, others return only a CSS string like
            // "background:transparent url(...) ...". If it's CSS-only, wrap it.
            if (typeof out === 'string') {
                var s = out.trim();
                if (s && s.indexOf('<') === -1 && s.indexOf('background') !== -1) {
                    // Ensure it ends with a semicolon for CSS safety
                    if (s.slice(-1) !== ';') s += ';';
                    return '<span class="picon" style="' + escape(s) + '"></span>';
                }
            }
            return out || '';
        }
    } catch (e) {}
    return '';
}


function formatLevelRange(minLvl, maxLvl) {
    if (!minLvl && !maxLvl) return '';
    if (!maxLvl || minLvl === maxLvl) return 'L' + minLvl;
    return 'L' + minLvl + '–' + maxLvl;
}

function buildEncounterRows(locationKey) {
    var loc = BattleLocationdex && BattleLocationdex[locationKey];
    if (!loc) return [];

    var rows = [];
    function pushSection(label) { rows.push({ kind: 'section', label: label }); }
    function pushMon(rate, minLvl, maxLvl, species) {
        rows.push({ kind: 'mon', rate: rate, min: minLvl, max: maxLvl, species: species });
    }

    // --- helper: normalize containers that can be arrays or {encs:[...]} ---
    function normalizeEncArray(encContainer) {
        if (!encContainer) return null;
        if (Array.isArray(encContainer)) return encContainer;
        if (typeof encContainer === 'object' && Array.isArray(encContainer.encs)) return encContainer.encs;
        return null;
    }

    // --- fallback rates by table size (when not provided) ---
    function defaultRatesForLen(n) {
        // Standard encounter slot weights often used by projects
        if (n === 12) return [20, 20, 10, 10, 10, 10, 5, 5, 4, 4, 1, 1];
        if (n === 10) return [60, 20, 10, 5, 5, 0, 0, 0, 0, 0]; // rarely used; safe-ish
        if (n === 5)  return [60, 30, 5, 4, 1];
        if (n === 3)  return [60, 30, 10];
        return null;
    }

    // --- format rate as "NN%" ---
    function formatRate(v) {
        if (v == null || v === '') return '';
        // if already contains %, keep it
        if (typeof v === 'string' && v.indexOf('%') >= 0) return v;
        return String(v) + '%';
    }

    // --- select rates array for a section label ---
    function getRateArrayFor(label, encLen) {
        var ratesRoot = (BattleLocationdex && BattleLocationdex.rates) || (loc && loc.rates) || {};
        var arr = null;

        if (label === 'Land') {
            arr = ratesRoot.land || null;
        } else if (label === 'Surfing') {
            arr = ratesRoot.surf || null;
        } else if (label === 'Rock Smash') {
            // support both names
            arr = ratesRoot.rockSmash || ratesRoot.rocksmash || ratesRoot.rock || null;
        } else if (label === 'Old Rod') {
            // RHH 1.12 often uses rates.fish.old
            if (ratesRoot.oldRod) arr = ratesRoot.oldRod;
            else if (ratesRoot.fish && ratesRoot.fish.old) arr = ratesRoot.fish.old;
            else arr = null;
        }

        // If found but doesn't match length, ignore and fallback
        if (arr && encLen && arr.length !== encLen) arr = null;

        if (!arr) arr = defaultRatesForLen(encLen);
        return arr;
    }

    // --- helper: add a section from a container ---
    function addFromArray(label, encContainer) {
        var encArr = normalizeEncArray(encContainer);
        if (!encArr || !encArr.length) return;

        var rateArr = getRateArrayFor(label, encArr.length);

        pushSection(label);

        for (var i = 0; i < encArr.length; i++) {
            var enc = encArr[i] || {};

            var rate = '';
            if (rateArr && rateArr[i] != null && rateArr[i] !== 0) {
                rate = formatRate(rateArr[i]);
            } else if (enc.rate != null) {
                rate = formatRate(enc.rate);
            }

            var minLvl = enc.minLvl || enc.min || enc.level || enc.minLevel;
            var maxLvl = enc.maxLvl || enc.max || enc.maxLevel;

            pushMon(rate, minLvl, maxLvl, enc.species);
        }
    }

    // 1) Generic "encounters" list (compatibility)
    if (Array.isArray(loc.encounters)) {
        var byType = {};
        for (var i = 0; i < loc.encounters.length; i++) {
            var e = loc.encounters[i];
            if (!e) continue;
            var t = e.type || 'Land';
            if (!byType[t]) byType[t] = [];
            byType[t].push(e);
        }
        for (var t2 in byType) {
            pushSection(t2);
            var arr = byType[t2];
            for (var j = 0; j < arr.length; j++) {
                var e2 = arr[j];
                pushMon(formatRate(e2.rate), e2.minLvl, e2.maxLvl, e2.species);
            }
        }
        return rows;
    }

    // 2) RHH 1.12 style
    addFromArray('Land', loc.land);
    addFromArray('Surfing', loc.surf);
    addFromArray('Rock Smash', loc.rockSmash || loc.rocksmash || loc.rock);

    // Fishing: ONLY Old Rod in your hack (loc.fish / legacy loc.fishing)
    addFromArray('Old Rod', loc.fish || loc.fishing);

    return rows;
}



function renderEncounterTable(rows) {
    if (!rows || !rows.length) return '<p class="enc-empty">No encounters defined for this location.</p>';

    var buf = '';
    var inTable = false;

    function openTable() {
        if (inTable) return;
        inTable = true;
        buf += '<table class="enc-table"><thead><tr>';
        buf += '<th class="enc-mon-col">Pokémon</th>';
        buf += '<th class="enc-rate-col">Rate</th>';
        buf += '<th class="enc-lvl-col">Level</th>';
        buf += '</tr></thead><tbody>';
    }

    function closeTable() {
        if (!inTable) return;
        inTable = false;
        buf += '</tbody></table>';
    }

    for (var i = 0; i < rows.length; i++) {
        var row = rows[i];

        if (row.kind === 'section') {
            closeTable();
            buf += '<h3 class="enc-section-title">' + escape(row.label) + '</h3>';
            openTable();
            continue;
        }

        openTable();

        var sid = toID(row.species || '');
        if (!sid) continue;

        var sp = (Dex && Dex.species && Dex.species.get) ? Dex.species.get(sid) : null;
        var name = (sp && sp.name) ? sp.name : (row.species || sid);

        var icon = pokemonIconHTML(sid);
        var rateTxt = (row.rate != null && row.rate !== '')
            ? (String(row.rate).indexOf('%') >= 0 ? String(row.rate) : String(row.rate) + '%')
            : '';
        var lvlTxt = formatLevelRange(row.min, row.max);

        buf += '<tr>';
        buf += '<td class="enc-mon">';

        // IMPORTANT: push + hash link (file:// friendly)
        buf += '<a href="' + escape(dexLink('pokemon/' + sid)) + '" data-target="push" class="enc-mon-link">';
        if (icon) buf += icon + ' ';
        buf += '<span class="enc-mon-name">' + escape(name) + '</span>';
        buf += '</a>';

        buf += '</td>';
        buf += '<td class="enc-rate-col">' + escape(rateTxt) + '</td>';
        buf += '<td class="enc-lvl-col">' + escape(lvlTxt) + '</td>';
        buf += '</tr>';
    }

    closeTable();
    return buf;
}


// -----------------------------
// Main panel (Lucid-style)
// -----------------------------
var PokedexEncountersMainPanel = Panels.Panel.extend({
    initialize: function () {
        var fragment = Backbone.history && Backbone.history.getFragment ? Backbone.history.getFragment() : '';
        var buf = '';
        buf += '<div class="pfx-body pfx-encounters"><form class="pokedex">';
        buf += '<h1><a href="/" data-target="replace">Pok\u00e9dex</a></h1>';
        buf += '<h4>Modified from <a href="https://dex.pokemonshowdown.com/">Pok\u00e9mon Showdown Dex</a> for Porydex</h4>';
        buf += '<ul class="tabbar centered" style="margin-bottom: 18px">';
        buf += '<li><button class="button nav-first" value="">Search</button></li>';
        buf += '<li><button class="button" value="pokemon/">Pok\u00e9mon</button></li>';
        buf += '<li><button class="button cur" value="encounters/">Encounters</button></li>';
        buf += '<li><button class="button nav-last" value="moves/">Moves</button></li>';
        buf += '</ul>';
        buf += '<div class="searchboxwrapper"><input class="textbox searchbox" type="search" name="q" autocomplete="off" autofocus placeholder="Search locations..." /></div>';
        buf += '</form>';

        buf += '<div class="enc-layout">';
        buf += '  <div class="enc-left">';
        buf += '    <div class="enc-list-title">Location</div>';
        buf += '    <div class="enc-list"><ul class="enc-list-ul"></ul></div>';
        buf += '  </div>';
        buf += '  <div class="enc-right">';
        buf += '    <div class="enc-header"><h2 class="enc-title">Select a location</h2></div>';
        buf += '    <div class="enc-content"></div>';
        buf += '  </div>';
        buf += '</div>';

        buf += '</div>';

        this.$el.html(buf);

        this.$searchbox = this.$('.searchbox');
        this.$list = this.$('.enc-list-ul');
        this.$title = this.$('.enc-title');
        this.$content = this.$('.enc-content');

        this.buildLocationList();

        var self = this;
        this.$searchbox.on('input', function () { self.filterLocationList(); });

        // If we are already at /encounters/:location, show it (hash routing can do this on load)
        var frag = fragment || '';
        if (frag.indexOf('encounters/') === 0) {
            var locId = frag.slice('encounters/'.length);
            if (locId) this.showLocation(locId);
        }
    },

    events: {
        'submit form.pokedex': 'submitSearch',
        'click .tabbar button': 'clickTab',
        'click .enc-list a': 'clickLocation',
    },

    submitSearch: function (e) {
        e.preventDefault();
        // no-op; we filter on input
    },

    clickTab: function (e) {
        e.preventDefault();
        var val = (e.currentTarget && e.currentTarget.value) || '';
        this.app.go(val, this, true);
    },


   buildLocationList: function () {
    var tmp = [];
    var baseCounts = Object.create(null);

    // helper (local): normalize RHH container
    function normalizeEncArray(encContainer) {
        if (!encContainer) return null;
        if (Array.isArray(encContainer)) return encContainer;
        if (typeof encContainer === 'object' && Array.isArray(encContainer.encs)) return encContainer.encs;
        return null;
    }

    // helper (local): does this location actually have any encounters?
    function hasAnyEncounters(loc) {
        if (!loc) return false;

        // generic shape
        if (Array.isArray(loc.encounters) && loc.encounters.length) return true;

        // RHH 1.12 shape
        var land = normalizeEncArray(loc.land);
        if (land && land.length) return true;

        var surf = normalizeEncArray(loc.surf);
        if (surf && surf.length) return true;

        var rock = normalizeEncArray(loc.rockSmash || loc.rocksmash || loc.rock);
        if (rock && rock.length) return true;

        var fish = normalizeEncArray(loc.fish || loc.fishing);
        if (fish && fish.length) return true;

        return false;
    }

    // 1) collect + baseCounts for stripping trailing " 0"
    for (var k in BattleLocationdex) {
        if (!BattleLocationdex.hasOwnProperty(k)) continue;
        if (k === 'rates') continue;

        var loc = BattleLocationdex[k] || {};
        var raw = loc.name || k;
        var clean = cleanLocationName(raw);

        // Ignore legacy / unused maps
        if (/unused/i.test(clean)) continue;

        // Count base names for trailing " <digits>" suffix
        var m = String(clean).match(/^(.*)\s(\d+)$/);
        if (m) {
            var base = (m[1] || '').trim();
            if (base) baseCounts[base] = (baseCounts[base] || 0) + 1;
        }

        tmp.push({
            key: k,
            raw: raw,
            clean: clean,
            hasEnc: hasAnyEncounters(loc)
        });
    }

    // 2) build items + dedupe by display name
    var byName = Object.create(null); // name -> item
    for (var i = 0; i < tmp.length; i++) {
        var t = tmp[i];

        var name = stripTrailingZeroIfSingle(t.clean, baseCounts);

        var item = { key: t.key, raw: t.raw, name: name, hasEnc: t.hasEnc };

        // Deduplicate: keep the one that actually has encounters.
        // If both have encounters (or both don't), keep the first one we saw.
        var prev = byName[name];
        if (!prev) {
            byName[name] = item;
        } else {
            if (!prev.hasEnc && item.hasEnc) byName[name] = item;
        }
    }

    // 3) finalize list
    var items = [];
    for (var n in byName) {
    if (!Object.prototype.hasOwnProperty.call(byName, n)) continue;
    items.push({ key: byName[n].key, raw: byName[n].raw, name: byName[n].name });
    }


    this._locationBaseCounts = baseCounts;

    items.sort(function (a, b) {
        var an = (a.name || '').toLowerCase();
        var bn = (b.name || '').toLowerCase();
        if (an < bn) return -1;
        if (an > bn) return 1;
        return 0;
    });

    this._allLocations = items;
    this.renderLocationList(items);
    },




    filterLocationList: function () {
        var q = toID(this.$searchbox.val() || '');
        if (!q) {
            this.renderLocationList(this._allLocations);
            return;
        }
        var out = [];
        for (var i = 0; i < this._allLocations.length; i++) {
            var it = this._allLocations[i];
            if (toID(it.name).indexOf(q) >= 0 || toID(it.raw).indexOf(q) >= 0) out.push(it);
        }
        this.renderLocationList(out);
    },

    renderLocationList: function (items) {
        // items: [{key, name}, ...]
        if (!items || !items.length) {
            this.$list.html('');
            return;
        }

        function computeBaseCandidate(name) {
            if (!name) return '';
            var idx = name.indexOf(' - ');
            if (idx > 0) return name.slice(0, idx).trim();

            // trailing " <digits>" (e.g. "Dewford Meadow 0")
            var m = name.match(/^(.*)\s(\d+)$/);
            if (m) return m[1].trim();

            return '';
        }

        // Count base candidates
        var counts = Object.create(null);
        for (var i = 0; i < items.length; i++) {
            var nm = items[i].name || '';
            var base = computeBaseCandidate(nm);
            if (!base) continue;
            counts[base] = (counts[base] || 0) + 1;
        }

        // Build groups preserving order
        var used = Object.create(null);
        var groups = []; // {type:'group', base, children:[...]} or {type:'single', item}

        for (var j = 0; j < items.length; j++) {
            var it = items[j];
            if (used[it.key]) continue;

            var name = it.name || '';
            var baseCand = computeBaseCandidate(name);

            var isDashGroup = (name.indexOf(' - ') > 0);
            var canGroup = baseCand && (isDashGroup || ((counts[baseCand] || 0) > 1));

            if (!canGroup) {
                groups.push({ type: 'single', item: it });
                used[it.key] = true;
                continue;
            }

            var children = [];
            for (var k = 0; k < items.length; k++) {
                var it2 = items[k];
                if (used[it2.key]) continue;

                var base2 = computeBaseCandidate(it2.name || '');
                if (base2 === baseCand) {
                    children.push(it2);
                    used[it2.key] = true;
                }
            }

            if (children.length <= 1) {
                groups.push({ type: 'single', item: children[0] || it });
                continue;
            }

            groups.push({ type: 'group', base: baseCand, children: children });
        }

        function renderItemLink(item) {
            return '<a href="' + escape(dexLink('encounters/' + item.key)) + '" class="enc-loc-link">' +
                escape(item.name) + '</a>';
        }

        function normKey(s) {
            return String(s || '').toLowerCase().replace(/\s+/g, ' ').trim();
        }

        var groupBases = Object.create(null);
        for (var gi = 0; gi < groups.length; gi++) {
            if (groups[gi].type === 'group') {
                groupBases[normKey(groups[gi].base)] = true;
            }
        }

        var buf = '';
        for (var g = 0; g < groups.length; g++) {
            var gr = groups[g];

            if (gr.type === 'single') {
                // If there is already a collapsible group with the same base name,
                // hide the standalone entry (avoids "Cave of Origin" appearing twice).
                if (groupBases[normKey(gr.item.name)]) continue;
            
                buf += '<li class="enc-loc-item">' + renderItemLink(gr.item) + '</li>';
                continue;
            }


            buf += '<li class="enc-loc-group">';
            buf += '<details class="enc-loc-details">';
            buf += '<summary class="enc-loc-summary">' + escape(gr.base) + '</summary>';
            buf += '<ul class="enc-loc-sublist">';

            for (var c = 0; c < gr.children.length; c++) {
                buf += '<li class="enc-loc-subitem">' + renderItemLink(gr.children[c]) + '</li>';
            }

            buf += '</ul>';
            buf += '</details>';
            buf += '</li>';
        }

        this.$list.html(buf);
    },


    clickLocation: function (e) {
        e.preventDefault();
        var href = e.currentTarget && e.currentTarget.getAttribute('href');
        if (!href) return;
        // href is like "#encounters/<key>" (see renderLocationList)
        var frag = href.charAt(0) === '#' ? href.slice(1) : href;
        if (frag.indexOf('encounters/') === 0) {
            var key = frag.slice('encounters/'.length);
            // Update URL and render.
            if (window.Panels && Panels.app && typeof Panels.app.navigate === 'function') {
                Panels.app.navigate('encounters/' + key, {trigger: false, replace: false});
            }
            this.showLocation(key);
        }
    },

    showLocation: function (locationIdOrKey) {
        var key = getLocationKeyFromIdOrName(locationIdOrKey);
        if (!key) return;
        var loc = BattleLocationdex[key] || {};
        var title = cleanLocationName(loc.name || key);
        title = stripTrailingZeroIfSingle(title, this._locationBaseCounts);
        this.$title.text(title);

        var rows = buildEncounterRows(key);
        this.$content.html(renderEncounterTable(rows));
    }
});

// -----------------------------
// Detail panel (right-side panel)
// -----------------------------
var PokedexEncountersPanel = PokedexResultPanel.extend({
    initialize: function (id) {
        this.id = id;
        this.locationKey = getLocationKeyFromIdOrName(id);
        this.render();
    },

    render: function () {
        var key = this.locationKey;
        var loc = (key && BattleLocationdex) ? BattleLocationdex[key] : null;
        var title = cleanLocationName((loc && (loc.name || key)) || this.id);

        var rows = key ? buildEncounterRows(key) : [];
        var html = '';
        html += '<div class="pfx-body pfx-encounters-detail">';
        html += '<h1>' + escape(title) + '</h1>';
        html += '<div class="enc-detail-content">' + renderEncounterTable(rows) + '</div>';
        html += '</div>';

        this.$el.html(html);
    }
});
