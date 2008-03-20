require 'open-uri'
require 'fileutils'

module PopplerTestUtils
  def ensure_dir(dir)
    FileUtils.mkdir_p(dir)
    dir
  end

  def test_dir
    File.expand_path(File.dirname(__FILE__))
  end

  def fixtures_dir
    ensure_dir(File.join(test_dir, "fixtures"))
  end

  def tmp_dir
    ensure_dir(File.join(test_dir, "tmp"))
  end

  def form_pdf
    file = File.join(fixtures_dir, "form.pdf")
    return file if File.exist?(file)
    pdf = open("http://www.irs.gov/pub/irs-pdf/fw9.pdf").read
    File.open(file, "wb") do |output|
      output.print(pdf)
    end
    file
  end

  def later_version?(major, minor, micro)
    (Poppler::BUILD_VERSION <=> [major, minor, micro]) >= 0
  end
end