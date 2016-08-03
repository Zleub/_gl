-- @Author: adebray
-- @Date:   2016-07-16 01:08:42
-- @Last Modified by:   adebray
-- @Last Modified time: 2016-07-16 01:59:46

for i=1,40 do
	for j=1,80 do
		if (math.pow(i, 2) + math.pow(j, 2) > math.pow(21, 2)) then
			io.write('#')
		else
			io.write(' ')
		end
	end
	io.write('\n')
end
