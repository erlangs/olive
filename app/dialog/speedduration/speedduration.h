#ifndef SPEEDDURATIONDIALOG_H
#define SPEEDDURATIONDIALOG_H

#include <QCheckBox>
#include <QDialog>

#include "node/block/clip/clip.h"
#include "node/output/track/track.h"
#include "widget/slider/floatslider.h"
#include "widget/slider/timeslider.h"
#include "undo/undocommand.h"

class SpeedDurationDialog : public QDialog
{
  Q_OBJECT
public:
  SpeedDurationDialog(const rational& timebase, const QList<ClipBlock*>& clips, QWidget* parent = nullptr);

public slots:
  virtual void accept() override;

private:
  double GetUnadjustedLengthTimestamp(ClipBlock* clip) const;

  int64_t GetAdjustedDuration(ClipBlock* clip, const double& new_speed) const;

  double GetAdjustedSpeed(ClipBlock* clip, const int64_t& new_duration) const;

  QList<ClipBlock*> clips_;

  FloatSlider* speed_slider_;
  TimeSlider* duration_slider_;

  rational timebase_;

  QCheckBox* link_speed_and_duration_;
  QCheckBox* reverse_speed_checkbox_;
  QCheckBox* maintain_audio_pitch_checkbox_;
  QCheckBox* ripple_clips_checkbox_;

private slots:
  void SpeedChanged();

  void DurationChanged();
};

class BlockReverseCommand : public UndoCommand {
public:
  BlockReverseCommand(Block* block, QUndoCommand* parent = nullptr);

protected:
  virtual void redo_internal() override;
  virtual void undo_internal() override;

private:
  Block* block_;

};

#endif // SPEEDDURATIONDIALOG_H
