--[[ a "memory" game, implemented in lua and xlabel
  to run set

Include "path/to/file/memory.rc"
*Luafile "path/to/file/memory.lua"

and click Play! to play :-)
]]--
require "lsmodule"
require "evar"
module ("memory", package.seeall)

--- states to make sure the game doesnt start twice etc.
local NOT_STARTED = 0
local RUNNING = 1

-- the colors
local colors = { "#FF8000","#B35A00","#0066B3","#BFE4FF","#990099","#FF80FF","#CCFF00","#7A9900","#FF00FF","#FF0000","#0000FF", "#FF8000"}
-- copy the colors so we have each color twice ... these are the pairs
for i=1,#colors do
	table.insert(colors, colors[i])
end

--- shuffle the colors ... init the random
math.randomseed(os.time())
math.random() -- the first random number is not random ... yeah, dont ask ;-)
---simple shuffle function
function shuffle( t )
	local h
	local function swap(i,j) h=t[i] t[i] = t[j] t[j]=h end
	for i=1, #t do
		swap(i, math.random(i,#t))
	end
end

--- the game class
game = { state = NOT_STARTED}

--the Card class
local Card = {}

--- create the playfield
function game:init()
	self.state = NOT_STARTED
	self.score = lsmodule.xlabel.score -- the label to update
	self.turns = 0 -- how many turns
	self.lastcard = nil --last card drawn
	self.cards = {}
	self.pairs_left = 32 -- so we can find out when the game is over
	shuffle(colors) -- shuffle the colors
	self.score:create() -- create the label to display the score
	local xl, obj
	for k=0, 7 do -- 4 rows
		for i=0, 7 do -- 4 columns
			xl = lsmodule.xlabel[lsmodule.getname()] -- new label
			obj = Card:new( xl ) -- make a new Card instance
			obj.color = colors[1+(4*k+i)] -- assign a color
			xl.addtogroup = "card" -- some basic looks
			xl.x = 450 + i*50 --- positioning
			xl.y = 250 + k*50
			xl.onleftclick = lsmodule.callback( game.draw, game, obj) -- when a card is clicked do game:draw(card)
			xl:create() -- create the label.
			table.insert(game.cards, obj) -- save it for later when we destroy it again
		end
	end
end

function game:stop()
	self.state = NOT_STARTED
	for i,v in ipairs(self.cards) do 
		v.__xlabel__:destroy() -- destroy all the cards
	end
	self.score:destroy() -- destroy the scoreboard
end

--- create the game
function game:start()
	if self.state == NOT_STARTED then
		self:init() -- init the game
		self.state = RUNNING
	end
end

function game:won()
	lslua.message_box("Congratulations, you won the game in " .. self.turns .. " Turns!", "Memory")
	self:stop()
end

function game:draw( card )
	if card ~= self.lastcard then
		self.turns = self.turns +1
		self.score:settext( "Turns: " .. tostring( self.turns ))
		card:turn()
		if self.lastcard then -- there is a unmatched card laying open
			if self.lastcard.color == card.color then -- we hit a pair
				self.lastcard:finished() -- stop the cards from doing anything further
				card:finished()
				self.pairs_left = self.pairs_left-1 -- one pairs less to find
				if self.pairs_left == 0 then
					return self:won() -- no more pairs, we won
				end
				self.lastcard = nil -- the last card was in a pair, so we dont need it anymore
			else -- no match ... turn the old card around
				self.lastcard:turnback() 
				self.lastcard = card
			end
		else
			self.lastcard = card
		end
	end
end

function Card:turn() -- show a card
	self.__xlabel__:settext("")
	self.__xlabel__:refresh("colors", self.color)
end
function Card:turnback() -- hide it again
	self.__xlabel__:settext("?")
	self.__xlabel__:refresh("colors", evar.cardcolors)
end

function Card:finished() -- the pair was found, clicking it does nothing anymore
	self.__xlabel__.onleftclick = nil
end

function Card:new( xlabel ) -- Card class __init__ method.
	local obj = {}
	setmetatable(obj, self)
	self.__index =self
	obj.__xlabel__ = xlabel
	return obj
end
