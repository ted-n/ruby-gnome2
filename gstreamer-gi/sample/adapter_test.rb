#!/usr/bin/env ruby
# -*- coding: utf-8 -*-
#
# This sample code is a port of
# gstreamer/tests/examples/adapter/adapter_test.c. It is licensed
# under the terms of the GNU Library General Public License, version
# 2 or (at your option) later.
#
# Copyright (C) 2013  Ruby-GNOME2 Project Team
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

require "gst"
require "gst-base"
require "benchmark"

class TestAdapter
  def initialize
    @adapter = GstBase::Adapter.new
  end

  def test_take(params)
    # Feed data of fixed size, then retrieve it in a different size
    ntimes = params.tot_size / params.write_size

    ntimes.times do
      # buf = Gst::Buffer.new_allocate(nil, params.write_size)
      buf = Gst::Buffer.new
      buf.initialize_new_allocate(nil, params.write_size)
      break if buf.nil?
      buf.memset(0, 0, params.write_size)
      @adapter.push(buf)
    end

    loop do
      data = @adapter.take(params.read_size)
      break if data.nil?
    end
  end

  def test_take_buffer(params)
    # Feed data of fixed size, then retrieve it in a different size
    ntimes = params.tot_size / params.write_size

    ntimes.each do
      # buf = Gst::Buffer.new_allocate(params.write_size)
      buf.initialize_new_allocate(nil, params.write_size)
      break if buf.nil?
      buf.memset(0, 0, params.write_size)
      @adapter.push(buf)
    end

    loop do
      buf = @adapter.take_buffer(params.read_size)
      break if buf.nil?
    end
  end

  def run(params)
    puts "Running on #{params.tot_size} bytes, writing #{params.write_size} bytes/buf, reading #{params.read_size} bytes/buf"

    puts Benchmark::CAPTION
    puts Benchmark.measure {
      test_take(params)
    }
    # puts "Time for take test: #{dur - start} secs"

    puts Benchmark.measure {
      test_take_buffer(params)
    }
    # puts "Time for take_buffer test: #{dur - start} secs"

    puts
  end
end

# This test pushes 'n' buffers of 'write size' into an adapter, then reads
# them out in 'read size' sized pieces, using take and then take_buffer,
# and prints the timings

TestParams = Struct.new("TestParams", :tot_size, :read_size, :write_size)
params_sets = [
# These values put ~256MB in 1MB chunks in an adapter, then reads them out
# in 250kb blocks
  [256000000, 250000, 1000000],
# These values put ~256MB in 1KB chunks in an adapter, then reads them out
# in 200 bytes blocks
  [256000000,    200,    1000],
# These values put ~256MB in 200 bytes chunks in an adapter, then reads them
# out in 1000 bytes blocks
  [256000000,   1000,     200]
].collect do |tot_size, read_size, write_size|
  TestParams.new(tot_size, read_size, write_size)
end

Gst.init
GstBase.init

tester = TestAdapter.new
params_sets.each do |param|
  tester.run(param)
end
