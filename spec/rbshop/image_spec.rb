require 'spec_helper'
require 'tmpdir'

describe RBShop::Image do
	it 'should exist' do
		expect( described_class ).to eq(RBShop::Image)
  end

  context '.load' do
    it 'should load an image' do
      img = described_class.load fixture_path('cat.jpg')
      expect(img).to be_a(described_class)
    end
    it 'should return nil for an invalid image' do
      img = described_class.load fixture_path('x.jpg')
      expect(img).to be_nil
    end
  end

  context 'getters' do
    let(:img) do
      described_class.load fixture_path('cat.jpg')
    end

    describe '#width' do
      it 'should have the correct value' do
        expect(img.width).to eql(500)
      end
    end

    describe '#height' do
      it 'should have the correct value' do
        expect(img.height).to eql(400)
      end
    end
  end

  context 'filters' do
    let(:img) do
      described_class.load fixture_path('cat.jpg')
    end
    describe '#charcoal' do
      it 'should work with no arguments' do
        expect(img.charcoal).to be_a(described_class)
      end
      it 'should work with one argument' do
        expect(img.charcoal(1.0)).to be_a(described_class)
      end
      it 'should work with one argument' do
        expect{ img.charcoal("10") }.to raise_error
      end
    end
    describe '#blur' do
      it 'should work with no arguments' do
        expect(img.blur).to be_a(described_class)
      end
    end
  end

  context 'save' do
    let(:img) do
      described_class.load fixture_path('cat.jpg')
    end
    describe '#save' do
      it 'should save an image' do
        Dir.mktmpdir do |dir|
          path = "#{dir}/cat.jpg"
          img.save(path)
          expect( File.exists?(path) ).to be_true
        end
      end
      it 'should charcoal and save an image' do
        path = "cat-charcoal.jpg"
        img.charcoal
        img.save(path)
        expect( File.exists?(path) ).to be_true
        File.delete(path)
      end
    end
  end

  context 'hash' do
    let(:img) do
      described_class.load fixture_path('cat.jpg')
    end
    it 'hash is returned' do
      expect(img.dimensions).to be_a(Hash)
    end
  end
end